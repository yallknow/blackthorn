#pragma once

#ifndef _THORN_LIBRARY_SAFE_DEQUE_
#define _THORN_LIBRARY_SAFE_DEQUE_

#include <atomic>
#include <condition_variable>
#include <deque>
#include <mutex>

#include "thorn_library_preprocessor.hpp"

namespace thorn {
namespace library {

template <typename T>
class safe_deque final {
 public:
  explicit safe_deque() noexcept { _THORN_LIBRARY_LOG_FUNCTION_CALL_(); }
  /* virtual */ ~safe_deque() noexcept { _THORN_LIBRARY_LOG_FUNCTION_CALL_(); }

 public:
  void mf_push_back(const T& pcl_Item) noexcept {
    _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

    {
      const std::unique_lock<std::mutex> lc_lock(this->mv_Mutex);
      this->mv_Deque.emplace_back(pcl_Item);
    }

    this->mv_ConditionVariable.notify_one();
  }

  void mf_push_front(const T& pcl_Item) noexcept {
    _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

    {
      const std::unique_lock<std::mutex> lc_lock(this->mv_Mutex);
      this->mv_Deque.emplace_front(pcl_Item);
    }

    this->mv_ConditionVariable.notify_one();
  }

  T mf_pop_back() noexcept {
    _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

    std::unique_lock<std::mutex> lv_lock(this->mv_Mutex);

    this->mv_ConditionVariable.wait(lv_lock, [this]() noexcept -> bool {
      _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

      return !this->mv_Deque.empty() || this->mv_IsTerminated;
    });

    if (this->mv_IsTerminated) {
      return T{};
    }

    T lv_Item = this->mv_Deque.back();
    this->mv_Deque.pop_back();

    return lv_Item;
  }

  T mf_pop_front() noexcept {
    _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

    std::unique_lock<std::mutex> lv_lock(this->mv_Mutex);

    this->mv_ConditionVariable.wait(lv_lock, [this]() noexcept -> bool {
      _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

      return !this->mv_Deque.empty() || this->mv_IsTerminated;
    });

    if (this->mv_IsTerminated) {
      return T{};
    }

    T lv_Item = this->mv_Deque.front();
    this->mv_Deque.pop_front();

    return lv_Item;
  }

  void mf_clear() noexcept {
    _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

    const std::unique_lock<std::mutex> lc_lock(this->mv_Mutex);
    this->mv_Deque.clear();
  }

  void mf_terminate() noexcept {
    _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

    this->mv_IsTerminated = true;

    this->mv_ConditionVariable.notify_all();
  }

 private:
  std::deque<T> mv_Deque{};

  std::mutex mv_Mutex{};

  std::condition_variable mv_ConditionVariable{};

  std::atomic<bool> mv_IsTerminated{false};

 public:
  explicit safe_deque(const safe_deque& pcl_Other) noexcept = delete;
  explicit safe_deque(safe_deque&& pr_Other) noexcept = delete;

 public:
  safe_deque& operator=(const safe_deque& pcl_Other) noexcept = delete;
  safe_deque& operator=(safe_deque&& pr_Other) noexcept = delete;
};

}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_SAFE_DEQUE_
