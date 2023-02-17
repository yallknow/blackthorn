#pragma once

#ifndef _THORN_LIBRARY_POSTER_
#define _THORN_LIBRARY_POSTER_

#include <boost/asio.hpp>
#include <functional>

namespace thorn {
namespace library {

class poster final {
 public:
  explicit poster(boost::asio::io_context& pl_Context,
                  const std::function<void()>& pcl_Task) noexcept;
  /* virtual */ ~poster() noexcept;

 public:
  explicit poster(poster&& pr_Other) noexcept;

 public:
  void mf_cancel() noexcept;

 private:
  boost::asio::io_context& ml_Context;

 private:
  std::function<void()> mv_Task;

 public:
  explicit poster(const poster& pcl_Other) noexcept = delete;

 public:
  poster& operator=(const poster& pcl_Other) noexcept = delete;
  poster& operator=(poster&& pr_Other) noexcept = delete;
};

}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_POSTER_
