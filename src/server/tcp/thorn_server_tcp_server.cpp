#include "thorn_server_tcp_server.hpp"

#include <algorithm>
#include <boost/asio/post.hpp>
#include <boost/system/error_code.hpp>

#include "../../library/thorn_library_poster.hpp"
#include "../../library/thorn_library_preprocessor.hpp"
#include "../../library/thorn_library_time.hpp"

thorn::server::tcp::server::server(
    const std::uint16_t pc_Port, const std::uint32_t pc_ThreadPoolSize) noexcept
    : mc_Endpoint{boost::asio::ip::tcp::v4(), pc_Port},
      mv_Context{pc_ThreadPoolSize} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::server::tcp::server::~server() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

bool thorn::server::tcp::server::mpf_inner_run() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Context.mf_run();

  boost::asio::post(this->mv_Context.mf_get_context(),
                    [this]() noexcept -> void {
                      _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

                      this->mf_async_accept();
                    });

  return true;
}

bool thorn::server::tcp::server::mpf_inner_stop() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Context.mf_stop();

  const std::unique_lock<std::mutex> lc_Lock(this->mv_SessionsMutex);

  for (std::shared_ptr<session> pp_Session : this->mv_Sessions) {
    pp_Session->mf_stop();

    if (pp_Session->mf_is_running()) {
      _THORN_LIBRARY_LOG_WARNING_("Can't stop session!");
    }
  }

  this->mv_Sessions.clear();

  return true;
}

void thorn::server::tcp::server::mf_async_accept() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  static std::optional<boost::asio::ip::tcp::acceptor> lsv_OptionalAcceptor{
      std::nullopt};

  static std::optional<boost::asio::ip::tcp::socket> lsv_OptionalSocket{
      std::nullopt};

  lsv_OptionalAcceptor.emplace(boost::asio::ip::tcp::acceptor{
      this->mv_Context.mf_get_context(), this->mc_Endpoint});

  lsv_OptionalSocket.emplace(this->mv_Context.mf_get_context());

  lsv_OptionalAcceptor->async_accept(
      lsv_OptionalSocket.value(),
      [this](const boost::system::error_code pc_ErrorCode) noexcept -> void {
        _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

        thorn::library::poster lv_Callback{
            this->mv_Context.mf_get_context(), [this]() noexcept -> void {
              _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

              this->mf_async_accept();
            }};

        if (pc_ErrorCode) {
          _THORN_LIBRARY_ASYNC_LOG_ERROR_CODE_("Can't accept connection!",
                                               pc_ErrorCode);

          // NOTE: This means the end of the session
          if (pc_ErrorCode == boost::asio::error::eof ||
              pc_ErrorCode == boost::asio::error::connection_reset ||
              pc_ErrorCode == boost::asio::error::operation_aborted) {
            _THORN_LIBRARY_ASYNC_LOG_WARNING_("The end of the session!");

            lv_Callback.mf_cancel();
          }

          return;
        }

        _THORN_LIBRARY_ASYNC_LOG_INFO_("Connection accepted successfully.");

        std::shared_ptr<session> lp_NewSession{std::make_shared<session>(
            this->mv_Context.mf_get_context(),
            std::move(lsv_OptionalSocket.value()),
            std::to_string(std::hash<std::string>{}(
                thorn::library::time::msf_now_underscore())))};

        lp_NewSession->mf_run();

        if (!lp_NewSession->mf_is_running()) {
          _THORN_LIBRARY_ASYNC_LOG_ERROR_("Can't start session!");

          return;
        }

        _THORN_LIBRARY_ASYNC_LOG_INFO_("Session (" +
                                       lp_NewSession->mf_get_id() +
                                       ") started successfully.");

        const std::unique_lock<std::mutex> lc_Lock(this->mv_SessionsMutex);

        if (!this->mf_is_running()) {
          _THORN_LIBRARY_ASYNC_LOG_ERROR_(
              "The server has already been stopped!");

          lp_NewSession->mf_stop();

          if (lp_NewSession->mf_is_running()) {
            _THORN_LIBRARY_ASYNC_LOG_WARNING_("Can't stop session!");
          }

          return;
        }

        _THORN_LIBRARY_ASYNC_LOG_INFO_("Cleaning up stopped sessions.");

        this->mv_Sessions.erase(
            std::remove_if(this->mv_Sessions.begin(), this->mv_Sessions.end(),
                           [](std::shared_ptr<session> pp_Session) noexcept
                           -> bool { return !pp_Session->mf_is_running(); }),
            this->mv_Sessions.end());

        this->mv_Sessions.emplace_back(lp_NewSession);
      });
}
