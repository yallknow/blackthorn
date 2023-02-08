#include "thorn_library_tcp_acceptor.hpp"

#include <boost/system/error_code.hpp>

#include "../thorn_library_preprocessor.hpp"

thorn::library::tcp::acceptor::acceptor(boost::asio::io_context& pl_Context,
                                        const std::uint16_t pc_Port) noexcept
    : mv_Acceptor{pl_Context, boost::asio::ip::tcp::endpoint{
                                  boost::asio::ip::tcp::v4(), pc_Port}} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::library::tcp::acceptor::~acceptor() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

bool thorn::library::tcp::acceptor::mpf_inner_run() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_OptionalSocket.emplace(this->mv_Acceptor.get_executor());

  boost::system::error_code lv_ErrorCode{};
  this->mv_Acceptor.accept(this->mv_OptionalSocket.value(), lv_ErrorCode);

  if (lv_ErrorCode) {
    _THORN_LIBRARY_LOG_ERROR_CODE_("Can't accept!", lv_ErrorCode);

    return false;
  }

  _THORN_LIBRARY_LOG_INFO_("Connection accepted.");

  return true;
}
