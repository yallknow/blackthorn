#pragma once

#ifndef _THORN_LIBRARY_TCP_ABSTRACT_SOCKET_SUPPLIER_
#define _THORN_LIBRARY_TCP_ABSTRACT_SOCKET_SUPPLIER_

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

#include "thorn_library_tcp_abstract_socket_holder.hpp"

namespace thorn {
namespace library {
namespace tcp {
namespace abstract {

class socket_supplier /* final */ : public socket_holder {
 public:
  explicit socket_supplier(boost::asio::io_context& pl_Context,
                           const std::string_view pc_Address,
                           const std::uint16_t pc_Port) noexcept;
  virtual ~socket_supplier() noexcept override;

 public:
  void mf_set_address(const std::string_view pc_Address) noexcept;
  void mf_set_port(const std::uint16_t pc_Port) noexcept;

  std::optional<boost::asio::ip::tcp::socket> mf_get_socket() noexcept;

 protected:
  boost::asio::io_context& ml_Context;

 protected:
  std::string mv_Address;
  std::uint16_t mv_Port;

 public:
  explicit socket_supplier(const socket_supplier& pcl_Other) noexcept = delete;
  explicit socket_supplier(socket_supplier&& pr_Other) noexcept = delete;

 public:
  socket_supplier& operator=(const socket_supplier& pcl_Other) noexcept =
      delete;
  socket_supplier& operator=(socket_supplier&& pr_Other) noexcept = delete;
};

}  // namespace abstract
}  // namespace tcp
}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_TCP_ABSTRACT_SOCKET_SUPPLIER_
