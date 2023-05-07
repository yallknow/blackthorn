#pragma once

#ifndef _THORN_SERVER_TCP_SESSION_
#define _THORN_SERVER_TCP_SESSION_

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <string_view>

#include "../../library/thorn_library_message.hpp"
#include "abstract/thorn_server_tcp_abstract_session.hpp"

namespace thorn {
namespace server {
namespace tcp {

class session final : public abstract::session {
 public:
  explicit session(boost::asio::io_context& pl_Context,
                   boost::asio::ip::tcp::socket&& pr_Socket,
                   const std::string_view pc_SessionID) noexcept;
  /* virtual */ ~session() noexcept;

 private:
  std::shared_ptr<thorn::library::message> mpf_inner_process_request(
      const std::shared_ptr<thorn::library::message> pcp_Request) noexcept
      override final;

 public:
  explicit session(const session& pcl_Other) noexcept = delete;
  explicit session(session&& pr_Other) noexcept = delete;

 public:
  session& operator=(const session& pcl_Other) noexcept = delete;
  session& operator=(session&& pr_Other) noexcept = delete;
};

}  // namespace tcp
}  // namespace server
}  // namespace thorn

#endif  // !_THORN_SERVER_TCP_SESSION_
