#include "thorn_client_tcp_client.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <optional>

#include "../../library/thorn_library_preprocessor.hpp"

thorn::client::tcp::client::client(
    const std::string_view pc_Address, const std::uint16_t pc_Port,
    const std::uint32_t pc_ThreadPoolSize) noexcept
    : mc_Address{pc_Address},
      mc_Port{pc_Port},
      mv_Context{pc_ThreadPoolSize},
      mv_Connector{this->mv_Context.mf_get_context(), pc_Address, pc_Port},
      mv_Session{
          this->mv_Context.mf_get_context(),
          boost::asio::ip::tcp::socket{this->mv_Context.mf_get_context()}} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::client::tcp::client::~client() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

bool thorn::client::tcp::client::mpf_inner_run() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Context.mf_run();

  this->mv_Connector.mf_run();

  if (!this->mv_Connector.mf_is_running()) {
    _THORN_LIBRARY_LOG_ERROR_("Can't start connector!");

    return false;
  }

  _THORN_LIBRARY_LOG_INFO_("Connector started successfully.");

  std::optional<boost::asio::ip::tcp::socket> lv_OptionalSocket{
      this->mv_Connector.mf_get_socket()};

  if (!lv_OptionalSocket) {
    _THORN_LIBRARY_LOG_ERROR_("Unable to get socket from connector!");

    return false;
  }

  _THORN_LIBRARY_LOG_INFO_("Socket extracted successfully.");

  this->mv_Session.mf_set_socket(std::move(lv_OptionalSocket.value()));

  this->mv_Session.mf_run();

  if (!this->mv_Session.mf_is_running()) {
    _THORN_LIBRARY_LOG_ERROR_("Can't start session!");

    return false;
  }

  _THORN_LIBRARY_LOG_INFO_("Session started successfully.");

  return true;
}

bool thorn::client::tcp::client::mpf_inner_stop() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Context.mf_stop();

  this->mv_Connector.mf_stop();

  this->mv_Session.mf_stop();

  return true;
}
