#pragma once

#ifndef _THORN_TEST_TCP_ABSTRACT_NETWORK_UNIT_
#define _THORN_TEST_TCP_ABSTRACT_NETWORK_UNIT_

#include <boost/asio.hpp>
#include <optional>

#include "../../../library/thorn_library_context.hpp"

namespace thorn {
namespace test {
namespace tcp {
namespace abstract {

class network_unit /* final */ {
 public:
  explicit network_unit() noexcept;
  virtual ~network_unit() noexcept;

 protected:
  void mf_close_socket() noexcept;

 protected:
  thorn::library::context mv_Context{1u};

  std::optional<boost::asio::ip::tcp::socket> mv_OptionalSocket{std::nullopt};

 public:
  explicit network_unit(const network_unit& pcl_Other) noexcept = delete;
  explicit network_unit(network_unit&& pr_Other) noexcept = delete;

 public:
  network_unit& operator=(const network_unit& pcl_Other) noexcept = delete;
  network_unit& operator=(network_unit&& pr_Other) noexcept = delete;
};

}  // namespace abstract
}  // namespace tcp
}  // namespace test
}  // namespace thorn

#endif  // !_THORN_TEST_TCP_ABSTRACT_NETWORK_UNIT_
