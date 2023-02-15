#pragma once

#ifndef _THORN_TEST_TCP_ASYNC_ACCEPTOR_
#define _THORN_TEST_TCP_ASYNC_ACCEPTOR_

#include <boost/asio.hpp>
#include <cstdint>

#include "abstract/thorn_test_tcp_abstract_network_unit.hpp"

namespace thorn {
namespace test {
namespace tcp {

class async_acceptor final : public abstract::network_unit {
 public:
  explicit async_acceptor(const std::uint16_t pc_Port) noexcept;
  /* virtual */ ~async_acceptor() noexcept override;

 public:
  void mf_async_accept() noexcept;

 private:
  boost::asio::ip::tcp::acceptor mv_Acceptor;

 public:
  explicit async_acceptor(const async_acceptor& pcl_Other) noexcept = delete;
  explicit async_acceptor(async_acceptor&& pr_Other) noexcept = delete;

 public:
  async_acceptor& operator=(const async_acceptor& pcl_Other) noexcept = delete;
  async_acceptor& operator=(async_acceptor&& pr_Other) noexcept = delete;
};

}  // namespace tcp
}  // namespace test
}  // namespace thorn

#endif  // !_THORN_TEST_TCP_ASYNC_ACCEPTOR_
