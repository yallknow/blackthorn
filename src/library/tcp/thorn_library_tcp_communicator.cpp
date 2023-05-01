#include "thorn_library_tcp_communicator.hpp"

#include <boost/asio/bind_executor.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/system/error_code.hpp>
#include <cstdint>
#include <string>

#include "../thorn_library_poster.hpp"
#include "../thorn_library_preprocessor.hpp"
#include "../thorn_library_string_cast.hpp"

thorn::library::tcp::communicator::communicator(
    boost::asio::io_context& pl_Context,
    boost::asio::ip::tcp::socket&& pr_Socket,
    abstract::communicator_holder* const pcp_CommunitatorHolder) noexcept
    : mv_ReadStrand{pl_Context},
      mv_WriteStrand{pl_Context},
      mcp_CommunitatorHolder{pcp_CommunitatorHolder} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_OptionalSocket.emplace(std::move(pr_Socket));
}

thorn::library::tcp::communicator::~communicator() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

void thorn::library::tcp::communicator::mf_push_back(
    const std::shared_ptr<message> pcp_Message) noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  if (!this->mf_is_running()) {
    _THORN_LIBRARY_ASYNC_LOG_WARNING_(
        "Failed to add a message, the communicator is turned off!");

    return;
  }

  this->mv_WriteDeque.mf_push_back(pcp_Message);

  boost::asio::post(this->mv_ReadStrand.context(), [this]() noexcept -> void {
    _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

    this->mf_write();
  });
}

void thorn::library::tcp::communicator::mf_push_front(
    const std::shared_ptr<message> pcp_Message) noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  if (!this->mf_is_running()) {
    _THORN_LIBRARY_ASYNC_LOG_WARNING_(
        "Failed to add a message, the communicator is turned off!");

    return;
  }

  this->mv_WriteDeque.mf_push_front(pcp_Message);

  boost::asio::post(this->mv_ReadStrand.context(), [this]() noexcept -> void {
    _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

    this->mf_write();
  });
}

std::shared_ptr<thorn::library::message>
thorn::library::tcp::communicator::mf_pop_back() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  return this->mv_ReadDeque.mf_pop_back();
}

std::shared_ptr<thorn::library::message>
thorn::library::tcp::communicator::mf_pop_front() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  return this->mv_ReadDeque.mf_pop_front();
}

void thorn::library::tcp::communicator::mf_set_socket(
    boost::asio::ip::tcp::socket&& pr_Socket) noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();

  this->mv_OptionalSocket.emplace(std::move(pr_Socket));
}

void thorn::library::tcp::communicator::mf_read(
    const std::shared_ptr<message_header> pcp_MessageHeader) noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  std::shared_ptr<std::string> lp_ReadBuffer(
      std::make_shared<std::string>(sizeof(message_header), '\0'));

  if (pcp_MessageHeader) {
    lp_ReadBuffer->resize(pcp_MessageHeader->mc_BodySize);
  }

  if (!this->mv_OptionalSocket) {
    _THORN_LIBRARY_ASYNC_LOG_ERROR_("The socket has already been closed!");

    return;
  }

  boost::asio::async_read(
      this->mv_OptionalSocket.value(),
      boost::asio::mutable_buffer{(void*)lp_ReadBuffer->c_str(),
                                  lp_ReadBuffer->size()},
      boost::asio::transfer_exactly(lp_ReadBuffer->size()),
      boost::asio::bind_executor(
          this->mv_ReadStrand,
          [this, pcp_MessageHeader, lp_ReadBuffer](
              const boost::system::error_code pc_ErrorCode,
              std::uint64_t pc_BytesRead) noexcept -> void {
            _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

            poster lv_Callback{this->mv_ReadStrand.context(),
                               [this]() noexcept -> void {
                                 _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

                                 this->mf_read();
                               }};

            if (pc_ErrorCode) {
              if (pcp_MessageHeader) {
                _THORN_LIBRARY_ASYNC_LOG_ERROR_CODE_("Can't read message body!",
                                                     pc_ErrorCode);
              } else {
                _THORN_LIBRARY_ASYNC_LOG_ERROR_CODE_(
                    "Can't read message header!", pc_ErrorCode);
              }

              // NOTE: This means the end of the session
              if (pc_ErrorCode == boost::asio::error::eof ||
                  pc_ErrorCode == boost::asio::error::connection_reset ||
                  pc_ErrorCode == boost::asio::error::operation_aborted) {
                _THORN_LIBRARY_ASYNC_LOG_WARNING_("The end of the session!");

                lv_Callback.mf_cancel();

                this->mf_stop();

                if (this->mcp_CommunitatorHolder) {
                  boost::asio::post(
                      this->mv_ReadStrand.context(), [this]() noexcept -> void {
                        _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

                        this->mcp_CommunitatorHolder->mpf_on_disconnect();
                      });
                }
              }

              return;
            }

            if (pcp_MessageHeader) {
              _THORN_LIBRARY_ASYNC_LOG_INFO_("Message body successfully read.");

              this->mv_ReadDeque.mf_push_back(std::make_shared<message>(
                  *pcp_MessageHeader, *lp_ReadBuffer));

              if (this->mcp_CommunitatorHolder) {
                boost::asio::post(
                    this->mv_ReadStrand.context(), [this]() noexcept -> void {
                      _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

                      this->mcp_CommunitatorHolder->mpf_on_message();
                    });
              }

              return;
            }

            const message_header lc_MessageHeader{
                string_cast<message_header>::msf_make_value(*lp_ReadBuffer)};

            if (!lc_MessageHeader.mc_BodySize) {
              _THORN_LIBRARY_ASYNC_LOG_INFO_(
                  "Message header successfully read.");

              this->mv_ReadDeque.mf_push_back(
                  std::make_shared<message>(lc_MessageHeader, std::string{}));

              if (this->mcp_CommunitatorHolder) {
                boost::asio::post(
                    this->mv_ReadStrand.context(), [this]() noexcept -> void {
                      _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

                      this->mcp_CommunitatorHolder->mpf_on_message();
                    });
              }

              return;
            }

            _THORN_LIBRARY_ASYNC_LOG_INFO_(
                "Scheduling the reading of the message body.");

            lv_Callback.mf_cancel();

            this->mf_read(std::make_shared<message_header>(lc_MessageHeader));
          }));
}

void thorn::library::tcp::communicator::mf_write() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  const std::shared_ptr<message> lcp_MessageToWrite{
      this->mv_WriteDeque.mf_pop_front()};

  if (!lcp_MessageToWrite) {
    _THORN_LIBRARY_ASYNC_LOG_ERROR_("Received message is empty!");

    return;
  }

  const std::string lp_WriteBuffer{string_cast<message_header>::msf_make_string(
                                       lcp_MessageToWrite->mc_Header) +
                                   lcp_MessageToWrite->mv_Body};

  if (!this->mv_OptionalSocket) {
    _THORN_LIBRARY_ASYNC_LOG_ERROR_("The socket has already been closed!");

    return;
  }

  boost::asio::async_write(
      this->mv_OptionalSocket.value(),
      boost::asio::mutable_buffer{(void*)(lp_WriteBuffer.c_str()),
                                  lp_WriteBuffer.size()},
      boost::asio::transfer_exactly(lp_WriteBuffer.size()),
      boost::asio::bind_executor(
          this->mv_WriteStrand,
          [this, lcp_MessageToWrite](
              const boost::system::error_code pc_ErrorCode,
              const std::uint64_t pc_BytesWritten) noexcept -> void {
            _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

            if (pc_ErrorCode) {
              _THORN_LIBRARY_ASYNC_LOG_ERROR_CODE_("Can't write message!",
                                                   pc_ErrorCode);

              // NOTE: This means the end of the session
              if (pc_ErrorCode == boost::asio::error::eof ||
                  pc_ErrorCode == boost::asio::error::connection_reset ||
                  pc_ErrorCode == boost::asio::error::operation_aborted) {
                _THORN_LIBRARY_ASYNC_LOG_WARNING_("The end of the session!");

                this->mf_stop();

                if (this->mcp_CommunitatorHolder) {
                  boost::asio::post(
                      this->mv_WriteStrand.context(),
                      [this]() noexcept -> void {
                        _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

                        this->mcp_CommunitatorHolder->mpf_on_disconnect();
                      });
                }
              }

              // NOTE: We will try to send this request later
              this->mf_push_front(lcp_MessageToWrite);

              return;
            }

            _THORN_LIBRARY_ASYNC_LOG_INFO_(
                "The message was successfully written.");
          }));
}

bool thorn::library::tcp::communicator::mpf_inner_run() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  if (!this->mv_OptionalSocket || !this->mv_OptionalSocket->is_open()) {
    _THORN_LIBRARY_LOG_ERROR_("The socket is invalid!");

    return false;
  }

  boost::asio::post(this->mv_ReadStrand.context(), [this]() noexcept -> void {
    _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

    this->mf_read();
  });

  return true;
}

bool thorn::library::tcp::communicator::mpf_inner_stop() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_close_socket();

  this->mv_ReadDeque.mf_terminate();
  this->mv_WriteDeque.mf_terminate();

  this->mv_ReadDeque.mf_clear();
  this->mv_WriteDeque.mf_clear();

  return true;
}
