#include "thorn_server_tcp_abstract_session.hpp"

#include <mutex>

#include "../../../library/thorn_library_preprocessor.hpp"

thorn::server::tcp::abstract::session::session(
    boost::asio::io_context& pl_Context,
    boost::asio::ip::tcp::socket&& pr_Socket,
    const std::string_view pc_SessionID) noexcept
    : thorn::library::tcp::abstract::node{pl_Context, std::move(pr_Socket)},
      mc_SessionID{pc_SessionID} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::server::tcp::abstract::session::~session() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

void thorn::server::tcp::abstract::session::mpf_on_disconnect() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  _THORN_LIBRARY_ASYNC_LOG_INFO_("Ending a " + this->mc_SessionID +
                                 " session.");

  this->mf_stop();
}

void thorn::server::tcp::abstract::session::mpf_on_message() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  this->mf_process_request();
}

std::string thorn::server::tcp::abstract::session::mf_get_id() const noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  return this->mc_SessionID;
}

void thorn::server::tcp::abstract::session::mf_process_request() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  std::shared_ptr<thorn::library::message> lp_Request{nullptr};

  lp_Request = this->mv_Communicator.mf_pop_front();

  if (!lp_Request) {
    _THORN_LIBRARY_ASYNC_LOG_ERROR_("Can't receive request!");

    return;
  }

  _THORN_LIBRARY_ASYNC_LOG_INFO_("Request received successfully.");

  const std::shared_ptr<thorn::library::message> lcp_Response{
      this->mpf_inner_process_request(lp_Request)};

  if (!lcp_Response) {
    _THORN_LIBRARY_ASYNC_LOG_ERROR_("Can't create response!");

    return;
  }

  _THORN_LIBRARY_ASYNC_LOG_INFO_("Response created successfully.");

  this->mv_Communicator.mf_push_back(lcp_Response);
}
