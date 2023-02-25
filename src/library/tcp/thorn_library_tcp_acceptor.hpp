#pragma once

#ifndef _THORN_LIBRARY_TCP_ACCEPTOR_
#define _THORN_LIBRARY_TCP_ACCEPTOR_

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdint>
#include <optional>
#include <string_view>

#include "abstract/thorn_library_tcp_abstract_socket_supplier.hpp"

namespace thorn {
namespace library {
namespace tcp {

class acceptor final : public abstract::socket_supplier {
 public:
  explicit acceptor(boost::asio::io_context& pl_Context,
                    const std::string_view pc_Address,
                    const std::uint16_t pc_Port) noexcept;
  /* virtual */ ~acceptor() noexcept override;

 private:
  void mf_close_acceptor() noexcept;

 private:
  bool mpf_inner_run() noexcept override;
  bool mpf_inner_stop() noexcept override;

 private:
  std::optional<boost::asio::ip::tcp::acceptor> mv_OptionalAcceptor{
      std::nullopt};

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
