#include "thorn_library_thread_pool.hpp"

#include "thorn_library_preprocessor.hpp"

thorn::library::thread_pool::thread_pool(
    const std::function<void()>& pcl_Task,
    const std::uint32_t pc_ThreadPoolSize) noexcept
    : mc_Task{pcl_Task}, mv_ThreadPoolSize{pc_ThreadPoolSize} {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  if (!this->mv_ThreadPoolSize) {
    _THORN_LIBRARY_LOG_WARNING_("Applying the default thread pool size!");

    constexpr std::uint32_t lc_DefaultThreadPoolSize{2u};
    this->mv_ThreadPoolSize = lc_DefaultThreadPoolSize;
  }
}

thorn::library::thread_pool::~thread_pool() {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  if (this->mf_is_running()) {
    this->mf_stop();
  }
}

bool thorn::library::thread_pool::mpf_inner_run() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  this->mv_ThreadPool.reserve(this->mv_ThreadPoolSize);

  while (this->mv_ThreadPool.size() < this->mv_ThreadPoolSize) {
    this->mv_ThreadPool.emplace_back(this->mc_Task);
  }

  return true;
}

bool thorn::library::thread_pool::mpf_inner_stop() noexcept {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  for (std::thread& ll_Thread : this->mv_ThreadPool) {
    if (ll_Thread.joinable()) {
      ll_Thread.join();
    }
  }

  this->mv_ThreadPool.clear();

  return true;
}
