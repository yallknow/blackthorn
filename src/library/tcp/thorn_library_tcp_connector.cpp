#include "thorn_library_tcp_connector.hpp"

#include <boost/system/error_code.hpp>

#include "../thorn_library_preprocessor.hpp"

thorn::library::tcp::connector::connector(boost::asio::io_context& pl_Context,
                                          const std::string_view pc_Address,
                                          const std::uint16_t pc_Port) noexcept
    : socket_holder{pl_Context}, mv_Address{pc_Address}, mv_Port{pc_Port} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::library::tcp::connector::~connector() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

void thorn::library::tcp::connector::mf_set_address(
    const std::string_view pc_Address) noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Address = pc_Address;
}

void thorn::library::tcp::connector::mf_set_port(
    const std::uint16_t pc_Port) noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Port = pc_Port;
}

bool thorn::library::tcp::connector::mpf_inner_run() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  boost::system::error_code lv_ErrorCode{};
  const boost::asio::ip::tcp::endpoint lc_Endpoint{
      boost::asio::ip::make_address(this->mv_Address, lv_ErrorCode),
      this->mv_Port};

  if (lv_ErrorCode) {
    _THORN_LIBRARY_LOG_ERROR_CODE_("Can't create endpoint!", lv_ErrorCode);

    return false;
  }

  _THORN_LIBRARY_LOG_INFO_("Endpoint created.");

  this->mv_OptionalSocket.emplace(this->ml_Context);

  this->mv_OptionalSocket->connect(lc_Endpoint, lv_ErrorCode);

  if (lv_ErrorCode) {
    _THORN_LIBRARY_LOG_ERROR_CODE_("Can't connect!", lv_ErrorCode);

    return false;
  }

  _THORN_LIBRARY_LOG_INFO_("Connection established.");

  return true;
}

bool thorn::library::tcp::connector::mpf_inner_stop() noexcept {
  this->mf_close_socket();

  return true;
}
