#pragma once

#ifndef _THORN_LIBRARY_TCP_ACCEPTOR_
#define _THORN_LIBRARY_TCP_ACCEPTOR_

#include <boost/asio.hpp>
#include <cstdint>

#include "abstract/thorn_library_tcp_abstract_socket_holder.hpp"

namespace thorn {
namespace library {
namespace tcp {

class acceptor final : public abstract::socket_holder {
 public:
  explicit acceptor(boost::asio::io_context& pl_Context,
                    const std::uint16_t pc_Port) noexcept;
  /* virtual */ ~acceptor() noexcept override;

 private:
  bool mpf_inner_run() noexcept override;

 private:
  boost::asio::ip::tcp::acceptor mv_Acceptor;

 public:
  explicit acceptor(const acceptor& pcl_Other) noexcept = delete;
  explicit acceptor(acceptor&& pr_Other) noexcept = delete;

 public:
  acceptor& operator=(const acceptor& pcl_Other) noexcept = delete;
  acceptor& operator=(acceptor&& pr_Other) noexcept = delete;
};

}  // namespace tcp
}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_TCP_ACCEPTOR_
