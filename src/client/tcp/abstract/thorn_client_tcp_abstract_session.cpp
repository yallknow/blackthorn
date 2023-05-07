#include "thorn_client_tcp_abstract_session.hpp"

#include <mutex>

#include "../../../library/thorn_library_preprocessor.hpp"

thorn::client::tcp::abstract::session::session(
    boost::asio::io_context& pl_Context,
    boost::asio::ip::tcp::socket&& pr_Socket) noexcept
    : thorn::library::tcp::abstract::node{pl_Context, std::move(pr_Socket)} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Steps.emplace_back([this]() noexcept -> void {
    _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

    this->mf_create_request();
  });
}

thorn::client::tcp::abstract::session::~session() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

void thorn::client::tcp::abstract::session::mpf_on_disconnect() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

void thorn::client::tcp::abstract::session::mpf_on_message() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  this->mf_process_response();
}

void thorn::client::tcp::abstract::session::mf_create_request() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  const std::shared_ptr<thorn::library::message> lcp_Requset{
      this->mpf_inner_create_request()};

  if (!lcp_Requset) {
    _THORN_LIBRARY_ASYNC_LOG_ERROR_("Can't create request!");

    return;
  }

  _THORN_LIBRARY_ASYNC_LOG_INFO_("Request created successfully.");

  this->mv_Communicator.mf_push_back(lcp_Requset);
}

void thorn::client::tcp::abstract::session::mf_process_response() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  std::shared_ptr<thorn::library::message> lp_Response{nullptr};

  lp_Response = this->mv_Communicator.mf_pop_front();

  if (!lp_Response) {
    _THORN_LIBRARY_ASYNC_LOG_ERROR_("Can't receive response!");

    return;
  }

  _THORN_LIBRARY_ASYNC_LOG_INFO_("Response received successfully.");

  this->mpf_inner_process_response(lp_Response);
}
