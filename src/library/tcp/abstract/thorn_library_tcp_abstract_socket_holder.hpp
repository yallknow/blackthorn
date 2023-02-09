#pragma once

#ifndef _THORN_LIBRARY_ABSTRACT_SOCKET_HOLDER_
#define _THORN_LIBRARY_ABSTRACT_SOCKET_HOLDER_

#include <boost/asio.hpp>
#include <optional>

#include "../../abstract/thorn_library_abstract_runnable.hpp"

namespace thorn {
namespace library {
namespace tcp {
namespace abstract {

class socket_holder /* final */ : public thorn::library::abstract::runnable {
 public:
  explicit socket_holder() noexcept;
  virtual ~socket_holder() noexcept override;

 public:
  std::optional<boost::asio::ip::tcp::socket> mf_get_socket() noexcept;

 private:
  bool mpf_inner_stop() noexcept override;

 protected:
  std::optional<boost::asio::ip::tcp::socket> mv_OptionalSocket{std::nullopt};

 public:
  explicit socket_holder(const socket_holder& pcl_Other) noexcept = delete;
  explicit socket_holder(socket_holder&& pr_Other) noexcept = delete;

 public:
  socket_holder& operator=(const socket_holder& pcl_Other) noexcept = delete;
  socket_holder& operator=(socket_holder&& pr_Other) noexcept = delete;
};

}  // namespace abstract
}  // namespace tcp
}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_ABSTRACT_SOCKET_HOLDER_
