#pragma once

#ifndef _THORN_CLIENT_TCP_SESSION_
#define _THORN_CLIENT_TCP_SESSION_

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>

#include "../../library/thorn_library_message.hpp"
#include "abstract/thorn_client_tcp_abstract_session.hpp"

namespace thorn {
namespace client {
namespace tcp {

class session final : public abstract::session {
 public:
  explicit session(boost::asio::io_context& pl_Context,
                   boost::asio::ip::tcp::socket&& pr_Socket) noexcept;
  /* virtual */ ~session() noexcept override;

 private:
  std::shared_ptr<thorn::library::message> mpf_inner_create_request() noexcept
      final;

  void mpf_inner_process_response(const std::shared_ptr<thorn::library::message>
                                      pcp_Response) noexcept final;

 public:
  explicit session(const session& pcl_Other) noexcept = delete;
  explicit session(session&& pr_Other) noexcept = delete;

 public:
  session& operator=(const session& pcl_Other) noexcept = delete;
  session& operator=(session&& pr_Other) noexcept = delete;
};

}  // namespace tcp
}  // namespace client
}  // namespace thorn

#endif  // !_THORN_CLIENT_TCP_SESSION_
