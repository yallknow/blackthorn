#include "thorn_library_tcp_abstract_socket_holder.hpp"

#include <boost/system/error_code.hpp>

#include "../../thorn_library_preprocessor.hpp"

thorn::library::tcp::abstract::socket_holder::socket_holder(
    boost::asio::io_context& pl_Context) noexcept
    : ml_Context{pl_Context} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::library::tcp::abstract::socket_holder::~socket_holder() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

std::optional<boost::asio::ip::tcp::socket>
thorn::library::tcp::abstract::socket_holder::mf_get_socket() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  // NOTE: You should only call this method if mf_is_running returns true
  if (!this->mf_is_running()) {
    _THORN_LIBRARY_LOG_WARNING_("Unable to get socket!");

    return std::nullopt;
  }

  std::optional<boost::asio::ip::tcp::socket> lv_OptionalSocketHolder{
      std::nullopt};
  lv_OptionalSocketHolder.swap(this->mv_OptionalSocket);

  // NOTE: Socket holder doesn't run without a working socket
  this->mf_stop();

  return lv_OptionalSocketHolder;
}

void thorn::library::tcp::abstract::socket_holder::mf_close_socket() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  if (!this->mv_OptionalSocket) {
    return;
  }

  boost::system::error_code lv_ErrorCode{};
  this->mv_OptionalSocket->close(lv_ErrorCode);

  if (lv_ErrorCode) {
    _THORN_LIBRARY_LOG_WARNING_("Can't close socket!");
  }

  this->mv_OptionalSocket.reset();
}
