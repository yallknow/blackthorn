#pragma once

#ifndef _THORN_LIBRARY_TCP_ABSTRACT_NODE_
#define _THORN_LIBRARY_TCP_ABSTRACT_NODE_

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <functional>
#include <vector>

#include "thorn_library_tcp_abstract_communicator_holder.hpp"

namespace thorn {
namespace library {
namespace tcp {
namespace abstract {

class node /* final */ : public communicator_holder {
 public:
  explicit node(boost::asio::io_context& pl_Context,
                boost::asio::ip::tcp::socket&& pr_Socket) noexcept;
  virtual ~node() noexcept override;

 public:
  bool mf_set_socket(boost::asio::ip::tcp::socket&& pr_Socket) noexcept;

 private:
  void mf_loop() noexcept;

 private:
  bool mpf_inner_run() noexcept override;
  bool mpf_inner_stop() noexcept override;

 protected:
  boost::asio::io_context& ml_Context;

 protected:
  std::vector<std::function<void()>> mv_Steps{};

 public:
  explicit node(const node& pcl_Other) noexcept = delete;
  explicit node(node&& pr_Other) noexcept = delete;

 public:
  node& operator=(const node& pcl_Other) noexcept = delete;
  node& operator=(node&& pr_Other) noexcept = delete;
};

}  // namespace abstract
}  // namespace tcp
}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_TCP_ABSTRACT_NODE_
