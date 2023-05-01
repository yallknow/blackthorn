#include "thorn_test_fixture.hpp"

#include "../library/thorn_library_log_builder.hpp"
#include "../library/thorn_library_logger.hpp"
#include "../library/thorn_library_scope_profiler.hpp"

thorn::test::fixture::fixture() noexcept {
  thorn::library::logger::msf_set_log_directory("log/test/");
  thorn::library::logger::msf_init();

  if (!thorn::library::logger::msf_is_initialized()) {
    return;
  }

  thorn::library::scope_profiler::msf_init();
  thorn::library::log_builder::msf_init();
}

thorn::test::fixture::~fixture() noexcept {
  if (!thorn::library::logger::msf_is_initialized()) {
    return;
  }

  thorn::library::scope_profiler::msf_destroy();
  thorn::library::log_builder::msf_destroy();
  thorn::library::logger::msf_destroy();
}
