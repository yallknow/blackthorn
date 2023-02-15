#include "thorn_test_tcp_async_connector.hpp"

#include <boost/system/error_code.hpp>

#include "../../library/thorn_library_preprocessor.hpp"

thorn::test::tcp::async_connector::async_connector(
    const std::string_view pc_Address, const std::uint16_t pc_Port) noexcept
    : mc_Address{pc_Address}, mc_Port{pc_Port} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::test::tcp::async_connector::~async_connector() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

void thorn::test::tcp::async_connector::mf_async_connect() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  this->mf_close_socket();
  this->mv_OptionalSocket.emplace(this->mv_Context.mf_get_context());

  boost::system::error_code lv_ErrorCode{};
  const boost::asio::ip::tcp::endpoint lc_Endpoint{
      boost::asio::ip::make_address(this->mc_Address, lv_ErrorCode),
      this->mc_Port};

  if (lv_ErrorCode) {
    _THORN_LIBRARY_ASYNC_LOG_ERROR_CODE_("Can't create endpoint!",
                                         lv_ErrorCode);

    return;
  }

  this->mv_OptionalSocket->async_connect(
      lc_Endpoint,
      [this](const boost::system::error_code pc_ErrorCode) -> void {
        _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

        if (pc_ErrorCode) {
          _THORN_LIBRARY_ASYNC_LOG_ERROR_CODE_("Can't connect!", pc_ErrorCode);
        } else {
          _THORN_LIBRARY_ASYNC_LOG_INFO_("Connected.");
        }

        this->mf_async_connect();
      });
}
