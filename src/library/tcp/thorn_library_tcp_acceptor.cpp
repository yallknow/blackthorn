#include "thorn_library_tcp_acceptor.hpp"

#include <boost/system/error_code.hpp>

#include "../thorn_library_preprocessor.hpp"

thorn::library::tcp::acceptor::acceptor(boost::asio::io_context& pl_Context,
                                        const std::string_view pc_Address,
                                        const std::uint16_t pc_Port) noexcept
    : abstract::socket_supplier{pl_Context, pc_Address, pc_Port} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::library::tcp::acceptor::~acceptor() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

void thorn::library::tcp::acceptor::mf_close_acceptor() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  if (!this->mv_OptionalAcceptor) {
    return;
  }

  boost::system::error_code lv_ErrorCode{};
  this->mv_OptionalAcceptor->close(lv_ErrorCode);

  if (lv_ErrorCode) {
    _THORN_LIBRARY_LOG_WARNING_("Can't close acceptor!");
  }

  this->mv_OptionalAcceptor.reset();
}

bool thorn::library::tcp::acceptor::mpf_inner_run() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_OptionalSocket.emplace(this->ml_Context);

  this->mv_OptionalAcceptor.emplace(
      this->ml_Context, boost::asio::ip::tcp::endpoint{
                            boost::asio::ip::tcp::v4(), this->mc_Port});

  boost::system::error_code lv_ErrorCode{};
  this->mv_OptionalAcceptor->accept(this->mv_OptionalSocket.value(),
                                    lv_ErrorCode);

  this->mf_close_acceptor();

  if (lv_ErrorCode) {
    _THORN_LIBRARY_LOG_ERROR_CODE_("Can't accept!", lv_ErrorCode);

    return false;
  }

  _THORN_LIBRARY_LOG_INFO_("Connection accepted.");

  return true;
}

bool thorn::library::tcp::acceptor::mpf_inner_stop() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_close_socket();

  return true;
}
