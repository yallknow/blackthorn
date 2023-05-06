#include "thorn_library_tcp_abstract_node.hpp"

#include <boost/asio/post.hpp>
#include <mutex>

#include "../../thorn_library_preprocessor.hpp"

thorn::library::tcp::abstract::node::node(
    boost::asio::io_context& pl_Context,
    boost::asio::ip::tcp::socket&& pr_Socket) noexcept
    : communicator_holder{pl_Context, std::move(pr_Socket)},
      ml_Context{pl_Context} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::library::tcp::abstract::node::~node() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

bool thorn::library::tcp::abstract::node::mf_set_socket(
    boost::asio::ip::tcp::socket&& pr_Socket) noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  return this->mv_Communicator.mf_set_socket(std::move(pr_Socket));
}

void thorn::library::tcp::abstract::node::mf_loop() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  for (const auto& pcl_Step : this->mv_Steps) {
    if (!this->mf_is_running()) {
      _THORN_LIBRARY_ASYNC_LOG_WARNING_("The node has already been stopped!");

      return;
    }

    _THORN_LIBRARY_ASYNC_LOG_INFO_("Starting the next step.");

    pcl_Step();
  }

  boost::asio::post(this->ml_Context, [this]() noexcept -> void {
    _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

    this->mf_loop();
  });
}

bool thorn::library::tcp::abstract::node::mpf_inner_run() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Communicator.mf_run();

  if (!this->mv_Communicator.mf_is_running()) {
    _THORN_LIBRARY_LOG_ERROR_("Can't run communicator!");

    return false;
  }

  _THORN_LIBRARY_LOG_INFO_("Communicator started successfully.");

  if (!this->mv_Steps.size()) {
    _THORN_LIBRARY_LOG_WARNING_("No work to run in a loop!");

    return true;
  }

  boost::asio::post(this->ml_Context, [this]() noexcept -> void {
    _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

    this->mf_loop();
  });

  return true;
}

bool thorn::library::tcp::abstract::node::mpf_inner_stop() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_Communicator.mf_stop();

  return true;
}
