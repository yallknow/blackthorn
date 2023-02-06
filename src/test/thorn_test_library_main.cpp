#define BOOST_TEST_MODULE thorn_test_library_main

#include <boost/test/included/unit_test.hpp>

#include "../library/abstract/thorn_library_abstract_runnable.hpp"
#include "../library/thorn_library_focused_thread_pool.hpp"
#include "../library/thorn_library_log_builder.hpp"
#include "../library/thorn_library_logger.hpp"
#include "../library/thorn_library_preprocessor.hpp"
#include "thorn_test_fixture.hpp"

BOOST_AUTO_TEST_CASE(thorn_test_library_test_case_log_builder) {
  thorn::library::log_builder::msf_set_log_directory("log/test/log_builder/");

  // NOTE: Log_builder is uninitialized from the start
  BOOST_CHECK(!thorn::library::log_builder::msf_is_initialized());

  // NOTE: msf_init() call on an uninitialized log_builder
  thorn::library::log_builder::msf_init();
  BOOST_CHECK(thorn::library::log_builder::msf_is_initialized());

  // NOTE: msf_init() call on an initialized log_builder
  thorn::library::log_builder::msf_init();
  BOOST_CHECK(thorn::library::log_builder::msf_is_initialized());

  // NOTE: msf_close() call on an initialized log_builder
  thorn::library::log_builder::msf_destroy();
  BOOST_CHECK(!thorn::library::log_builder::msf_is_initialized());

  // NOTE: msf_close() call on an uninitialized log_builder
  thorn::library::log_builder::msf_destroy();
  BOOST_CHECK(!thorn::library::log_builder::msf_is_initialized());

  // NOTE: Re-initializing a log_builder
  thorn::library::log_builder::msf_init();
  BOOST_CHECK(thorn::library::log_builder::msf_is_initialized());

  // NOTE: Stopping a re-initialized log_builder
  thorn::library::log_builder::msf_destroy();
  BOOST_CHECK(!thorn::library::log_builder::msf_is_initialized());
}

BOOST_AUTO_TEST_CASE(thorn_test_library_test_case_logger) {
  thorn::library::logger::msf_set_log_directory("log/test/logger/");

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

BOOST_AUTO_TEST_SUITE(thorn_test_library_test_suite,
                      *boost::unit_test::fixture<thorn::test::fixture>())

void thorn_test_library_test_case_abstract_runnable(
    std::shared_ptr<thorn::library::abstract::runnable> pp_RunnableClass) {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  // NOTE: Object is valid
  BOOST_CHECK(pp_RunnableClass);

  // NOTE: Object is not running from the start
  BOOST_CHECK(!pp_RunnableClass->mf_is_running());

  // NOTE: mf_run() call on a non-running object
  pp_RunnableClass->mf_run();
  BOOST_CHECK(pp_RunnableClass->mf_is_running());

  // NOTE: mf_run() call on a running object
  pp_RunnableClass->mf_run();
  BOOST_CHECK(pp_RunnableClass->mf_is_running());

  // NOTE: mf_stop() call on a running object
  pp_RunnableClass->mf_stop();
  BOOST_CHECK(!pp_RunnableClass->mf_is_running());

  // NOTE: mf_stop() call on a non-running object
  pp_RunnableClass->mf_stop();
  BOOST_CHECK(!pp_RunnableClass->mf_is_running());

  // NOTE: Restarting an object
  pp_RunnableClass->mf_run();
  BOOST_CHECK(pp_RunnableClass->mf_is_running());

  // NOTE: Stopping a restarted Object
  pp_RunnableClass->mf_stop();
  BOOST_CHECK(!pp_RunnableClass->mf_is_running());
};

BOOST_AUTO_TEST_CASE(thorn_test_library_test_case_focused_thread_pool) {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  thorn_test_library_test_case_abstract_runnable(
      std::make_shared<thorn::library::focused_thread_pool>([]() -> void {}));
}

BOOST_AUTO_TEST_SUITE_END()
