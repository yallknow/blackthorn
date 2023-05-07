#include "../library/thorn_library_log_builder.hpp"
#include "../library/thorn_library_logger.hpp"
#include "../library/thorn_library_preprocessor.hpp"
#include "../library/thorn_library_scope_profiler.hpp"
#include "tcp/thorn_server_tcp_server.hpp"

static int sf_server_main() {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  thorn::server::tcp::server lv_Server{15001, 2};

  lv_Server.mf_run();

  if (!lv_Server.mf_is_running()) {
    _THORN_LIBRARY_LOG_ERROR_("Can't start server!");

    return EXIT_FAILURE;
  }

  _THORN_LIBRARY_LOG_INFO_("Server started successfully.");

  static constexpr std::chrono::seconds lsc_SleepDuration{45u};
  std::this_thread::sleep_for(lsc_SleepDuration);

  lv_Server.mf_stop();

  if (lv_Server.mf_is_running()) {
    _THORN_LIBRARY_LOG_ERROR_("Can't stop server!");

    return EXIT_FAILURE;
  }

  _THORN_LIBRARY_LOG_INFO_("Server stopped successfully.");

  return EXIT_SUCCESS;
}

int main() {
  thorn::library::logger::msf_set_log_directory("log/server/");
  thorn::library::logger::msf_init();

  if (!thorn::library::logger::msf_is_initialized()) {
    return EXIT_FAILURE;
  }

  thorn::library::scope_profiler::msf_init();
  thorn::library::log_builder::msf_init();

  if (!thorn::library::scope_profiler::msf_is_initialized() ||
      !thorn::library::log_builder::msf_is_initialized()) {
    return EXIT_FAILURE;
  }

  const int lc_ReturnValue{sf_server_main()};

  thorn::library::scope_profiler::msf_destroy();
  thorn::library::log_builder::msf_destroy();
  thorn::library::logger::msf_destroy();

  return lc_ReturnValue;
}
