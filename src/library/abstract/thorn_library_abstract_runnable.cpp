#include "thorn_library_abstract_runnable.hpp"

#include "../thorn_library_preprocessor.hpp"

thorn::library::abstract::runnable::runnable() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::library::abstract::runnable::~runnable() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

void thorn::library::abstract::runnable::mf_run() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  if (this->mv_IsRunning) {
    _THORN_LIBRARY_LOG_WARNING_("Runnable is already running!");

    return;
  }

  this->mv_IsRunning = this->mpf_inner_run();
}

void thorn::library::abstract::runnable::mf_stop() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  if (!this->mv_IsRunning) {
    _THORN_LIBRARY_LOG_WARNING_("Runnable already stopped!");

    return;
  }

  this->mv_IsRunning = !this->mpf_inner_stop();
}

bool thorn::library::abstract::runnable::mf_is_running() const noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  return this->mv_IsRunning;
}
