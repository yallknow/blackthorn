#include "thorn_library_tcp_abstract_node.hpp"

#include <boost/asio/post.hpp>

#include "../../thorn_library_preprocessor.hpp"

thorn::library::tcp::abstract::node::node(
    const std::string_view pc_Address, const std::uint16_t pc_Port,
    const std::uint32_t pc_ThreadPoolSize) noexcept
    : mc_Address{pc_Address},
      mc_Port{pc_Port},
      mc_ThreadPoolSize{pc_ThreadPoolSize} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::library::tcp::abstract::node::~node() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

void thorn::library::tcp::abstract::node::mf_loop() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  this->mpf_inner_loop();

  if (!this->mv_OptionalCommunicator) {
    _THORN_LIBRARY_ASYNC_LOG_WARNING_(
        "The communicator has already been stopped!");

    return;
  }

  boost::asio::post(this->mv_OptionalContext->mf_get_context(),
                    [this]() noexcept -> void {
                      _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

                      this->mf_loop();
                    });
}

bool thorn::library::tcp::abstract::node::mpf_inner_run() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_OptionalContext.emplace(this->mc_ThreadPoolSize);
  this->mv_OptionalContext->mf_run();

  this->mpf_emplace_socket_supplier(this->mv_OptionalContext->mf_get_context(),
                                    this->mc_Address, this->mc_Port);

  if (!this->mp_SocketSupplier) {
    _THORN_LIBRARY_LOG_ERROR_("Can't create socket supplier!");

    return false;
  }

  this->mp_SocketSupplier->mf_run();

  if (!this->mp_SocketSupplier->mf_is_running()) {
    _THORN_LIBRARY_LOG_ERROR_("Can't run socket supplier!");

    return false;
  }

  this->mv_OptionalCommunicator.emplace(
      this->mv_OptionalContext->mf_get_context(),
      this->mp_SocketSupplier->mf_get_socket().value());
  this->mv_OptionalCommunicator->mf_run();

  if (!this->mv_OptionalCommunicator->mf_is_running()) {
    _THORN_LIBRARY_LOG_ERROR_("Can't run communicator!");

    return false;
  }

  boost::asio::post(this->mv_OptionalContext->mf_get_context(),
                    [this]() noexcept -> void {
                      _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

                      this->mf_loop();
                    });

  return true;
}

bool thorn::library::tcp::abstract::node::mpf_inner_stop() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_OptionalCommunicator->mf_stop();
  this->mv_OptionalCommunicator.reset();

  this->mp_SocketSupplier->mf_stop();
  this->mp_SocketSupplier.reset();

  this->mv_OptionalContext->mf_stop();
  this->mv_OptionalContext.reset();

  return true;
}
