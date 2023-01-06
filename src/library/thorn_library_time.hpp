#pragma once

#ifndef _THORN_LIBRARY_TIME_
#define _THORN_LIBRARY_TIME_

#include <string>

namespace thorn {
namespace library {

class time final {
 public:
  static std::string msf_now() noexcept;
  static std::string msf_now_underscore() noexcept;

 public:
  explicit time() noexcept = delete;
  /* virtual */ ~time() noexcept = delete;

 public:
  explicit time(const time& pcl_Other) noexcept = delete;
  explicit time(time&& pr_Other) noexcept = delete;

 public:
  time& operator=(const time& pcl_Other) noexcept = delete;
  time& operator=(time&& pr_Other) noexcept = delete;
};

}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_TIME_
