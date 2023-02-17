#pragma once

#ifndef _THORN_TEST_TCP_ASYNC_CONNECTOR_
#define _THORN_TEST_TCP_ASYNC_CONNECTOR_

#include <cstdint>
#include <string>
#include <string_view>

#include "abstract/thorn_test_tcp_abstract_network_unit.hpp"

namespace thorn {
namespace test {
namespace tcp {

class async_connector final : public abstract::network_unit {
 public:
  explicit async_connector(const std::string_view pc_Address,
                           const std::uint16_t pc_Port) noexcept;
  /* virtual */ ~async_connector() noexcept override;

 public:
  void mf_set_address(const std::string_view pc_Address) noexcept;
  void mf_set_port(const std::uint16_t pc_Port) noexcept;

  void mf_async_connect() noexcept;

 private:
  std::string mv_Address;
  std::uint16_t mv_Port;

 public:
  explicit async_connector(const async_connector& pcl_Other) noexcept = delete;
  explicit async_connector(async_connector&& pr_Other) noexcept = delete;

 public:
  async_connector& operator=(const async_connector& pcl_Other) noexcept =
      delete;
  async_connector& operator=(async_connector&& pr_Other) noexcept = delete;
};

}  // namespace tcp
}  // namespace test
}  // namespace thorn

#endif  // !_THORN_TEST_TCP_ASYNC_CONNECTOR_
