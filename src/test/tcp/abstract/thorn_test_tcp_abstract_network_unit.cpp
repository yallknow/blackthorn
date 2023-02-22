#include "thorn_test_tcp_abstract_network_unit.hpp"

#include "../../../library/thorn_library_preprocessor.hpp"

thorn::test::tcp::abstract::network_unit::network_unit() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Context.mf_run();
}

thorn::test::tcp::abstract ::network_unit::~network_unit() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Context.mf_stop();
}

void thorn::test::tcp::abstract::network_unit::mf_close_socket() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

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
