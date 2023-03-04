#include "thorn_library_tcp_abstract_node.hpp"

#include "../../thorn_library_preprocessor.hpp"

thorn::library::tcp::abstract::node::node() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::library::tcp::abstract::node::~node() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

bool thorn::library::tcp::abstract::node::mpf_inner_run() noexcept {
  this->mv_OptionalContext.emplace();
  this->mv_OptionalContext->mf_run();

  this->mpf_emplace_socket_supplier(this->mv_OptionalContext->mf_get_context());
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

  return true;
}

bool thorn::library::tcp::abstract::node::mpf_inner_stop() noexcept {
  this->mv_OptionalContext->mf_stop();
  this->mv_OptionalContext.reset();

  this->mp_SocketSupplier->mf_stop();
  this->mp_SocketSupplier.reset();

  this->mv_OptionalCommunicator->mf_stop();
  this->mv_OptionalCommunicator.reset();

  return true;
}
