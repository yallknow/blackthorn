#include "thorn_test_tcp_async_acceptor.hpp"

#include <boost/system/error_code.hpp>

#include "../../library/thorn_library_preprocessor.hpp"

thorn::test::tcp::async_acceptor::async_acceptor(
    const std::uint16_t pc_Port) noexcept
    : mv_Port{pc_Port} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::test::tcp::async_acceptor::~async_acceptor() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

void thorn::test::tcp::async_acceptor::mf_set_port(
    const std::uint16_t pc_Port) noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Port = pc_Port;
}

void thorn::test::tcp::async_acceptor::mf_close_acceptor() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  if (!this->mv_OptionalAcceptor) {
    return;
  }

  boost::system::error_code lv_ErrorCode{};
  this->mv_OptionalAcceptor->close(lv_ErrorCode);

  if (lv_ErrorCode) {
    _THORN_LIBRARY_ASYNC_LOG_WARNING_("Can't close acceptor!");
  }

  this->mv_OptionalAcceptor.reset();
}

void thorn::test::tcp::async_acceptor::mf_async_accept() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  this->mf_close_acceptor();
  this->mv_OptionalAcceptor.emplace(
      this->mv_Context.mf_get_context(),
      boost::asio::ip::tcp::endpoint{boost::asio::ip::tcp::v4(),
                                     this->mv_Port});

  this->mf_close_socket();
  this->mv_OptionalSocket.emplace(this->mv_Context.mf_get_context());

  this->mv_OptionalAcceptor->async_accept(
      this->mv_OptionalSocket.value(),
      [this](const boost::system::error_code pc_ErrorCode) noexcept -> void {
        _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

        if (pc_ErrorCode) {
          _THORN_LIBRARY_ASYNC_LOG_ERROR_CODE_("Can't accept!", pc_ErrorCode);
        } else {
          _THORN_LIBRARY_ASYNC_LOG_INFO_("Accepted.");
        }

        this->mf_async_accept();
      });
}
