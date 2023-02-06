#pragma once

#ifndef _THORN_LIBRARY_FOCUSED_THREAD_POOL_
#define _THORN_LIBRARY_FOCUSED_THREAD_POOL_

#include <cstdint>
#include <functional>
#include <thread>
#include <vector>

#include "abstract/thorn_library_abstract_runnable.hpp"

namespace thorn {
namespace library {

class focused_thread_pool final : public abstract::runnable {
 public:
  explicit focused_thread_pool(
      const std::function<void()>& pcl_Task,
      const std::uint32_t pc_ThreadPoolSize =
          std::thread::hardware_concurrency()) noexcept;
  /* virtual */ ~focused_thread_pool() noexcept override;

 private:
  bool mpf_inner_run() noexcept override;
  bool mpf_inner_stop() noexcept override;

 private:
  const std::function<void()> mc_Task;

 private:
  std::uint32_t mv_ThreadPoolSize{};
  std::vector<std::thread> mv_ThreadPool{};

 public:
  explicit focused_thread_pool(const focused_thread_pool& pcl_Other) noexcept =
      delete;
  explicit focused_thread_pool(focused_thread_pool&& pc_Other) noexcept =
      delete;

 public:
  focused_thread_pool& operator=(
      const focused_thread_pool& pcl_Other) noexcept = delete;
  focused_thread_pool& operator=(focused_thread_pool&& pc_Other) noexcept =
      delete;
};

}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_FOCUSED_THREAD_POOL_
