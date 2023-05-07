#pragma once

#ifndef _THORN_CLIENT_TCP_ABSTRACT_SESSION_
#define _THORN_CLIENT_TCP_ABSTRACT_SESSION_

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>

#include "../../../library/tcp/abstract/thorn_library_tcp_abstract_node.hpp"
#include "../../../library/thorn_library_message.hpp"

namespace thorn {
namespace client {
namespace tcp {
namespace abstract {

class session /* final */ : public thorn::library::tcp::abstract::node {
 public:
  explicit session(boost::asio::io_context& pl_Context,
                   boost::asio::ip::tcp::socket&& pr_Socket) noexcept;
  virtual ~session() noexcept override;

 private:
  void mpf_on_disconnect() noexcept override final;
  void mpf_on_message() noexcept override final;

 protected:
  virtual std::shared_ptr<thorn::library::message>
  mpf_inner_create_request() noexcept = 0;

  virtual void mpf_inner_process_response(
      const std::shared_ptr<thorn::library::message> pcp_Response) noexcept = 0;

 private:
  void mf_create_request() noexcept;
  void mf_process_response() noexcept;

 public:
  explicit session(const session& pcl_Other) noexcept = delete;
  explicit session(session&& pr_Other) noexcept = delete;

 public:
  session& operator=(const session& pcl_Other) noexcept = delete;
  session& operator=(session&& pr_Other) noexcept = delete;
};

}  // namespace abstract
}  // namespace tcp
}  // namespace client
}  // namespace thorn

#endif  // !_THORN_CLIENT_TCP_ABSTRACT_SESSION_
