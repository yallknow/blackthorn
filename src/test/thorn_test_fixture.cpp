#include "thorn_test_fixture.hpp"

#include "../library/thorn_library_log_builder.hpp"

thorn::test::fixture::fixture() noexcept {
  thorn::library::log_builder::msf_set_log_directory("log/test/");
  thorn::library::log_builder::msf_init();
}

thorn::test::fixture::~fixture() noexcept {
  thorn::library::log_builder::msf_destroy();
}
