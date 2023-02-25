#include "thorn_library_tcp_abstract_socket_holder.hpp"

#include <boost/system/error_code.hpp>

#include "../../thorn_library_preprocessor.hpp"

thorn::library::tcp::abstract::socket_holder::socket_holder() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::library::tcp::abstract::socket_holder::~socket_holder() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

void thorn::library::tcp::abstract::socket_holder::mf_close_socket() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  if (!this->mv_OptionalSocket) {
    return;
  }

  if (this->mv_OptionalSocket->is_open()) {
    boost::system::error_code lv_ErrorCode{};

    this->mv_OptionalSocket->shutdown(
        boost::asio::ip::tcp::socket::shutdown_both, lv_ErrorCode);

    if (lv_ErrorCode) {
      _THORN_LIBRARY_LOG_WARNING_("Can't shutdown socket!");
    }

    this->mv_OptionalSocket->close(lv_ErrorCode);

    if (lv_ErrorCode) {
      _THORN_LIBRARY_LOG_WARNING_("Can't close socket!");
    }
  }

  this->mv_OptionalSocket.reset();
}
