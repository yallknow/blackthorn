#include "thorn_server_tcp_session.hpp"

#include <cstdint>
#include <iostream>

#include "../../library/thorn_library_message_header.hpp"
#include "../../library/thorn_library_preprocessor.hpp"
#include "../../library/thorn_library_time.hpp"

thorn::server::tcp::session::session(
    boost::asio::io_context& pl_Context,
    boost::asio::ip::tcp::socket&& pr_Socket,
    const std::string_view pc_SessionID) noexcept
    : abstract::session{pl_Context, std::move(pr_Socket), pc_SessionID} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::server::tcp::session::~session() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

std::shared_ptr<thorn::library::message>
thorn::server::tcp::session::mpf_inner_process_request(
    const std::shared_ptr<thorn::library::message> pcp_Request) noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  std::cout << thorn::library::time::msf_now()
            << "[Session: " << this->mc_SessionID
            << "]: Message received: " << pcp_Request->mc_Header.mc_Code << ' '
            << pcp_Request->mc_Header.mc_Flags << ' '
            << pcp_Request->mc_Header.mc_BodySize << ' ' << pcp_Request->mv_Body
            << '\n';

  static constexpr std::string_view lsc_ResponseBody{"Pong"};
  static constexpr std::uint32_t lsc_ResponseBodySize{
      static_cast<std::uint32_t>(lsc_ResponseBody.size())};

  std::shared_ptr<thorn::library::message> lp_Response{
      std::make_shared<thorn::library::message>(
          thorn::library::message_header{0u, 0u, lsc_ResponseBodySize},
          lsc_ResponseBody.data())};

  std::cout << thorn::library::time::msf_now()
            << "[Session: " << this->mc_SessionID
            << "]: Message created: " << lp_Response->mc_Header.mc_Code << ' '
            << lp_Response->mc_Header.mc_Flags << ' '
            << lp_Response->mc_Header.mc_BodySize << ' ' << lp_Response->mv_Body
            << '\n';

  return lp_Response;
}
