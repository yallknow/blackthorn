#pragma once

#ifndef _THORN_LIBRARY_CONTEXT_
#define _THORN_LIBRARY_CONTEXT_

#include <boost/asio.hpp>
#include <cstdint>
#include <optional>
#include <thread>

#include "abstract/thorn_library_abstract_runnable.hpp"
#include "thorn_library_focused_thread_pool.hpp"

namespace thorn {
namespace library {

class context final : public abstract::runnable {
 public:
  explicit context(const std::uint32_t pc_ThreadPoolSize =
                       std::thread::hardware_concurrency()) noexcept;
  /* virtual */ ~context() noexcept override;

 public:
  boost::asio::io_context& mf_get_context() noexcept;

 private:
  bool mpf_inner_run() noexcept override;
  bool mpf_inner_stop() noexcept override;

 private:
  boost::asio::io_context mv_Context{};

  std::optional<
      boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>
      mv_OptionalWorkGuard{std::nullopt};

  focused_thread_pool mv_FocusedThreadPool;

 public:
  explicit context(const context& pcl_Other) noexcept = delete;
  explicit context(context&& pc_Other) noexcept = delete;

 public:
  context& operator=(const context& pcl_Other) noexcept = delete;
  context& operator=(context&& pc_Other) noexcept = delete;
};

}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_CONTEXT_
