#pragma once

#ifndef _THORN_LIBRARY_TCP_ABSTRACT_COMMUNICATOR_HOLDER_
#define _THORN_LIBRARY_TCP_ABSTRACT_COMMUNICATOR_HOLDER_

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "../../abstract/thorn_library_abstract_connection.hpp"
#include "../../abstract/thorn_library_abstract_runnable.hpp"
#include "../thorn_library_tcp_communicator.hpp"

namespace thorn {
namespace library {
namespace tcp {
namespace abstract {

class communicator_holder /* final */
    : public thorn::library::abstract::runnable,
      public thorn::library::abstract::connection {
 public:
  explicit communicator_holder(
      boost::asio::io_context& pl_Context,
      boost::asio::ip::tcp::socket&& pr_Socket) noexcept;
  virtual ~communicator_holder() noexcept override;

 protected:
  thorn::library::tcp::communicator mv_Communicator;

 public:
  explicit communicator_holder(const communicator_holder& pcl_Other) noexcept =
      delete;
  explicit communicator_holder(communicator_holder&& pr_Other) noexcept =
      delete;

 public:
  communicator_holder& operator=(
      const communicator_holder& pcl_Other) noexcept = delete;
  communicator_holder& operator=(communicator_holder&& pr_Other) noexcept =
      delete;
};

}  // namespace abstract
}  // namespace tcp
}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_TCP_ABSTRACT_COMMUNICATOR_HOLDER_
