#pragma once

#ifndef _THORN_CLIENT_TCP_CLIENT_
#define _THORN_CLIENT_TCP_CLIENT_

#include <cstdint>
#include <string>
#include <string_view>
#include <thread>

#include "../../library/abstract/thorn_library_abstract_runnable.hpp"
#include "../../library/tcp/thorn_library_tcp_connector.hpp"
#include "../../library/thorn_library_context.hpp"
#include "thorn_client_tcp_session.hpp"

namespace thorn {
namespace client {
namespace tcp {

class client final : public thorn::library::abstract::runnable {
 public:
  explicit client(const std::string_view pc_Address,
                  const std::uint16_t pc_Port,
                  const std::uint32_t pc_ThreadPoolSize =
                      std::thread::hardware_concurrency()) noexcept;
  /* virtual */ ~client() noexcept;

 private:
  bool mpf_inner_run() noexcept override final;
  bool mpf_inner_stop() noexcept override final;

 private:
  const std::string mc_Address;
  const std::uint16_t mc_Port;

 private:
  thorn::library::context mv_Context;

  thorn::library::tcp::connector mv_Connector;

  session mv_Session;

 public:
  explicit client(const client& pcl_Other) noexcept = delete;
  explicit client(client&& pr_Other) noexcept = delete;

 public:
  client& operator=(const client& pcl_Other) noexcept = delete;
  client& operator=(client&& pr_Other) noexcept = delete;
};

}  // namespace tcp
}  // namespace client
}  // namespace thorn

#endif  // !_THORN_CLIENT_TCP_CLIENT_
