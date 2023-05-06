#include "thorn_library_focused_thread_pool.hpp"

#include <string>

#include "thorn_library_preprocessor.hpp"

thorn::library::focused_thread_pool::focused_thread_pool(
    const std::function<void()>& pcl_Task,
    const std::uint32_t pc_ThreadPoolSize) noexcept
    : mc_Task{pcl_Task}, mv_ThreadPoolSize{pc_ThreadPoolSize} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  constexpr std::uint32_t lc_DefaultThreadPoolSize{2u};

  if (this->mv_ThreadPoolSize < lc_DefaultThreadPoolSize) {
    _THORN_LIBRARY_LOG_WARNING_("Applying the default thread pool size!");

    this->mv_ThreadPoolSize = lc_DefaultThreadPoolSize;
  }

  _THORN_LIBRARY_LOG_INFO_("A thread pool of size " +
                           std::to_string(this->mv_ThreadPoolSize) +
                           " has been created.");
}

thorn::library::focused_thread_pool::~focused_thread_pool() {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mf_stop();
}

bool thorn::library::focused_thread_pool::mpf_inner_run() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_ThreadPool.reserve(this->mv_ThreadPoolSize);

  while (this->mv_ThreadPool.size() < this->mv_ThreadPoolSize) {
    this->mv_ThreadPool.emplace_back(this->mc_Task);
  }

  return true;
}

bool thorn::library::focused_thread_pool::mpf_inner_stop() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  for (std::thread& pl_Thread : this->mv_ThreadPool) {
    if (pl_Thread.joinable()) {
      pl_Thread.join();
    }
  }

  this->mv_ThreadPool.clear();

  return true;
}
