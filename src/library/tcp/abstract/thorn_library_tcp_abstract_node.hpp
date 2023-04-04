#pragma once

#ifndef _THORN_LIBRARY_TCP_ABSTRACT_NODE_
#define _THORN_LIBRARY_TCP_ABSTRACT_NODE_

#include <boost/asio/io_context.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <thread>

#include "../../abstract/thorn_library_abstract_runnable.hpp"
#include "../../thorn_library_context.hpp"
#include "../thorn_library_tcp_communicator.hpp"
#include "thorn_library_tcp_abstract_socket_supplier.hpp"

namespace thorn {
namespace library {
namespace tcp {
namespace abstract {

class node /* final */ : public thorn::library::abstract::runnable {
 public:
  explicit node(const std::string_view pc_Address, const std::uint16_t pc_Port,
                const std::uint32_t pc_ThreadPoolSize =
                    std::thread::hardware_concurrency()) noexcept;
  virtual ~node() noexcept override;

 private:
  void mf_loop() noexcept;

 private:
  bool mpf_inner_run() noexcept override;
  bool mpf_inner_stop() noexcept override;

 protected:
  virtual void mpf_emplace_socket_supplier(
      boost::asio::io_context& pl_Context, const std::string_view pc_Address,
      const std::uint16_t pc_Port) noexcept = 0;

  virtual void mpf_inner_loop() noexcept = 0;

 private:
  const std::string mc_Address;
  const std::uint16_t mc_Port;
  const std::uint32_t mc_ThreadPoolSize;

 protected:
  std::optional<thorn::library::context> mv_OptionalContext{std::nullopt};
  std::optional<thorn::library::tcp::communicator> mv_OptionalCommunicator{
      std::nullopt};
  std::unique_ptr<socket_supplier> mp_SocketSupplier{nullptr};

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
