#include "thorn_client_tcp_session.hpp"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <string_view>
#include <thread>

#include "../../library/thorn_library_message_header.hpp"
#include "../../library/thorn_library_preprocessor.hpp"
#include "../../library/thorn_library_time.hpp"

thorn::client::tcp::session::session(
    boost::asio::io_context& pl_Context,
    boost::asio::ip::tcp::socket&& pr_Socket) noexcept
    : abstract::session{pl_Context, std::move(pr_Socket)} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::client::tcp::session::~session() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

std::shared_ptr<thorn::library::message>
thorn::client::tcp::session::mpf_inner_create_request() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  static constexpr std::chrono::seconds lsc_SleepDuration{3u};
  std::this_thread::sleep_for(lsc_SleepDuration);

  static constexpr std::string_view lsc_RequestBody{"Ping"};
  static constexpr std::uint32_t lsc_RequestBodySize{
      static_cast<std::uint32_t>(lsc_RequestBody.size())};

  std::shared_ptr<thorn::library::message> lp_Request{
      std::make_shared<thorn::library::message>(
          thorn::library::message_header{0u, 0u, lsc_RequestBodySize},
          lsc_RequestBody.data())};

  std::cout << thorn::library::time::msf_now()
            << ": Message created: " << lp_Request->mc_Header.mc_Code << ' '
            << lp_Request->mc_Header.mc_Flags << ' '
            << lp_Request->mc_Header.mc_BodySize << ' ' << lp_Request->mv_Body
            << '\n';

  return lp_Request;
}

void thorn::client::tcp::session::mpf_inner_process_response(
    const std::shared_ptr<thorn::library::message> pcp_Response) noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  std::cout << thorn::library::time::msf_now()
            << ": Message received: " << pcp_Response->mc_Header.mc_Code << ' '
            << pcp_Response->mc_Header.mc_Flags << ' '
            << pcp_Response->mc_Header.mc_BodySize << ' '
            << pcp_Response->mv_Body << '\n';
}
