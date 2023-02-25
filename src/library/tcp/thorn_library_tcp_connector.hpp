#pragma once

#ifndef _THORN_LIBRARY_TCP_CONNECTOR_
#define _THORN_LIBRARY_TCP_CONNECTOR_

#include <boost/asio/io_context.hpp>
#include <cstdint>
#include <string_view>

#include "abstract/thorn_library_tcp_abstract_socket_supplier.hpp"

namespace thorn {
namespace library {
namespace tcp {

class connector final : public abstract::socket_supplier {
 public:
  explicit connector(boost::asio::io_context& pl_Context,
                     const std::string_view pc_Address,
                     const std::uint16_t pc_Port) noexcept;
  /* virtual */ ~connector() noexcept override;

 private:
  bool mpf_inner_run() noexcept override;
  bool mpf_inner_stop() noexcept override;

 public:
  explicit connector(const connector& pcl_Other) noexcept = delete;
  explicit connector(connector&& pr_Other) noexcept = delete;

 public:
  connector& operator=(const connector& pcl_Other) noexcept = delete;
  connector& operator=(connector&& pr_Other) noexcept = delete;
};

}  // namespace tcp
}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_TCP_CONNECTOR_
