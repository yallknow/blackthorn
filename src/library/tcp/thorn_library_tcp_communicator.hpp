#pragma once

#ifndef _THORN_LIBRARY_TCP_COMMUNICATOR_
#define _THORN_LIBRARY_TCP_COMMUNICATOR_

#include <boost/asio/io_context.hpp>
#include <boost/asio/io_context_strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>

#include "../tcp/abstract/thorn_library_tcp_abstract_socket_holder.hpp"
#include "../thorn_library_message.hpp"
#include "../thorn_library_message_header.hpp"
#include "../thorn_library_safe_deque.hpp"

namespace thorn {
namespace library {
namespace tcp {

class communicator final : public abstract::socket_holder {
 public:
  // NOTE: Communicator should only accept open sockets
  explicit communicator(boost::asio::io_context& pl_Context,
                        boost::asio::ip::tcp::socket&& pr_Socket) noexcept;
  /* virtual */ ~communicator() noexcept override;

 public:
  void mf_push_back(const std::shared_ptr<message> pcp_Message) noexcept;
  void mf_push_front(const std::shared_ptr<message> pcp_Message) noexcept;

  std::shared_ptr<message> mf_pop_back() noexcept;
  std::shared_ptr<message> mf_pop_front() noexcept;

  // NOTE: Communicator should only accept open sockets
  void mf_set_socket(boost::asio::ip::tcp::socket&& pr_Socket) noexcept;

 private:
  // NOTE: We read the body if a message header is present
  void mf_read(const std::shared_ptr<message_header> pcp_MessageHeader =
                   nullptr) noexcept;
  void mf_write() noexcept;

 private:
  bool mpf_inner_run() noexcept override;
  bool mpf_inner_stop() noexcept override;

 private:
  boost::asio::io_context::strand mv_ReadStrand;
  boost::asio::io_context::strand mv_WriteStrand;

  safe_deque<std::shared_ptr<message>> mv_ReadDeque{};
  safe_deque<std::shared_ptr<message>> mv_WriteDeque{};

 public:
  explicit communicator(const communicator& pcl_Other) noexcept = delete;
  explicit communicator(communicator&& pr_Other) noexcept = delete;

 public:
  communicator& operator=(const communicator& pcl_Other) noexcept = delete;
  communicator& operator=(communicator&& pr_Other) noexcept = delete;
};

}  // namespace tcp
}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_TCP_COMMUNICATOR_
