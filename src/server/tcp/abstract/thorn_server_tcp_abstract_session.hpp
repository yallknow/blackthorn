#pragma once

#ifndef _THORN_SERVER_TCP_ABSTRACT_SESSION_
#define _THORN_SERVER_TCP_ABSTRACT_SESSION_

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <string>
#include <string_view>

#include "../../../library/tcp/abstract/thorn_library_tcp_abstract_node.hpp"
#include "../../../library/thorn_library_message.hpp"

namespace thorn {
namespace server {
namespace tcp {
namespace abstract {

class session /* final */ : public thorn::library::tcp::abstract::node {
 public:
  explicit session(boost::asio::io_context& pl_Context,
                   boost::asio::ip::tcp::socket&& pr_Socket,
                   const std::string_view pc_SessionID) noexcept;
  virtual ~session() noexcept override;

 private:
  void mpf_on_disconnect() noexcept override final;
  void mpf_on_message() noexcept override final;

 protected:
  virtual std::shared_ptr<thorn::library::message> mpf_inner_process_request(
      const std::shared_ptr<thorn::library::message> pcp_Request) noexcept = 0;

 public:
  std::string mf_get_id() const noexcept;

 private:
  void mf_process_request() noexcept;

 protected:
  const std::string mc_SessionID;

 public:
  explicit session(const session& pcl_Other) noexcept = delete;
  explicit session(session&& pr_Other) noexcept = delete;

 public:
  session& operator=(const session& pcl_Other) noexcept = delete;
  session& operator=(session&& pr_Other) noexcept = delete;
};

}  // namespace abstract
}  // namespace tcp
}  // namespace server
}  // namespace thorn

#endif  // !_THORN_SERVER_TCP_ABSTRACT_SESSION_
