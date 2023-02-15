#include "thorn_library_context.hpp"

#include "thorn_library_preprocessor.hpp"

thorn::library::context::context(const std::uint32_t pc_ThreadPoolSize) noexcept
    : mv_FocusedThreadPool{[this]() -> void {
                             if (this->mv_Context.stopped()) {
                               this->mv_Context.restart();
                             }

                             this->mv_Context.run();
                           },
                           pc_ThreadPoolSize} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();
}

thorn::library::context::~context() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

boost::asio::io_context& thorn::library::context::mf_get_context() noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  return this->mv_Context;
}

bool thorn::library::context::mpf_inner_run() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_OptionalWorkGuard.emplace(this->mv_Context.get_executor());

  this->mv_FocusedThreadPool.mf_run();

  return true;
}

bool thorn::library::context::mpf_inner_stop() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_OptionalWorkGuard.reset();

  this->mv_Context.stop();

  this->mv_FocusedThreadPool.mf_stop();

  return true;
}
