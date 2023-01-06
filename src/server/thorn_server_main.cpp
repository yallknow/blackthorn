#include "../library/thorn_library_log_builder.hpp"
#include "../library/thorn_library_preprocessor.hpp"

int f_server_main() {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  return EXIT_SUCCESS;
}

int main() {
  thorn::library::log_builder::msf_set_log_directory("log/server/");
  thorn::library::log_builder::msf_init();

  if (!thorn::library::log_builder::msf_is_initialized()) {
    return EXIT_FAILURE;
  }

  const int lc_ReturnValue{f_server_main()};

  thorn::library::log_builder::msf_destroy();
  return lc_ReturnValue;
}
