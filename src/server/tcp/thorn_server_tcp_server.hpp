#pragma once

#ifndef _THORN_SERVER_TCP_SERVER_
#define _THORN_SERVER_TCP_SERVER_

#include <boost/asio/ip/tcp.hpp>
#include <cstdint>
#include <mutex>
#include <optional>
#include <thread>
#include <vector>

#include "../../library/abstract/thorn_library_abstract_runnable.hpp"
#include "../../library/thorn_library_context.hpp"
#include "thorn_server_tcp_session.hpp"

namespace thorn {
namespace server {
namespace tcp {

class server final : public thorn::library::abstract::runnable {
 public:
  explicit server(const std::uint16_t pc_Port,
                  const std::uint32_t pc_ThreadPoolSize =
                      std::thread::hardware_concurrency()) noexcept;
  /* virtual */ ~server() noexcept override;

 private:
  bool mpf_inner_run() noexcept override final;
  bool mpf_inner_stop() noexcept override final;

 private:
  void mf_async_accept() noexcept;

 private:
  const boost::asio::ip::tcp::endpoint mc_Endpoint;

 private:
  thorn::library::context mv_Context;

  std::mutex mv_SessionsMutex{};

  std::vector<std::shared_ptr<session>> mv_Sessions{};

 public:
  explicit server(const server& pcl_Other) noexcept = delete;
  explicit server(server&& pr_Other) noexcept = delete;

 public:
  server& operator=(const server& pcl_Other) noexcept = delete;
  server& operator=(server&& pr_Other) noexcept = delete;
};

}  // namespace tcp
}  // namespace server
}  // namespace thorn

#endif  // !_THORN_SERVER_TCP_SERVER_
