#define BOOST_TEST_MODULE thorn_test_library_main

#include <boost/test/included/unit_test.hpp>

#include "../library/thorn_library_logger.hpp"

BOOST_AUTO_TEST_CASE(thorn_test_library_test_case_logger) {
  // NOTE: Logger is uninitialized from the start
  BOOST_CHECK(!thorn::library::logger::msf_is_initialized());

  // NOTE: msf_init() call on an uninitialized logger
  thorn::library::logger::msf_init();
  BOOST_CHECK(thorn::library::logger::msf_is_initialized());

  // NOTE: msf_init() call on an initialized logger
  thorn::library::logger::msf_init();
  BOOST_CHECK(thorn::library::logger::msf_is_initialized());

  // NOTE: msf_close() call on an initialized logger
  thorn::library::logger::msf_destroy();
  BOOST_CHECK(!thorn::library::logger::msf_is_initialized());

  // NOTE: msf_close() call on an uninitialized logger
  thorn::library::logger::msf_destroy();
  BOOST_CHECK(!thorn::library::logger::msf_is_initialized());

  // NOTE: Re-initializing a logger
  thorn::library::logger::msf_init();
  BOOST_CHECK(thorn::library::logger::msf_is_initialized());

  // NOTE: Stopping a re-initialized logger
  thorn::library::logger::msf_destroy();
  BOOST_CHECK(!thorn::library::logger::msf_is_initialized());
}
