#pragma once

#ifndef _THORN_LIBRARY_ABSTRACT_RUNNABLE_
#define _THORN_LIBRARY_ABSTRACT_RUNNABLE_

#include <atomic>

namespace thorn {
namespace library {
namespace abstract {

class runnable /* final */ {
 public:
  explicit runnable() noexcept;
  virtual ~runnable() noexcept;

 public:
  void mf_run() noexcept;
  void mf_stop() noexcept;

  bool mf_is_running() const noexcept;

 protected:
  virtual bool mpf_inner_run() noexcept = 0;
  virtual bool mpf_inner_stop() noexcept = 0;

 private:
  std::atomic<bool> mv_IsRunning{false};

 public:
  explicit runnable(const runnable& pcl_Other) noexcept = delete;
  explicit runnable(runnable&& pr_Other) noexcept = delete;

 public:
  runnable& operator=(const runnable& pcl_Other) noexcept = delete;
  runnable& operator=(runnable&& pr_Other) noexcept = delete;
};

}  // namespace abstract
}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_ABSTRACT_RUNNABLE_
