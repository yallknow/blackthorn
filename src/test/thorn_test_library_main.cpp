#define BOOST_TEST_MODULE thorn_test_library_main

#include <boost/asio.hpp>  // NOTE: Including asio first to avoid build errors
#include <boost/system/error_code.hpp>
#include <boost/test/included/unit_test.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <string_view>

#include "../library/abstract/thorn_library_abstract_runnable.hpp"
#include "../library/tcp/abstract/thorn_library_tcp_abstract_socket_holder.hpp"
#include "../library/tcp/thorn_library_tcp_acceptor.hpp"
#include "../library/tcp/thorn_library_tcp_connector.hpp"
#include "../library/thorn_library_context.hpp"
#include "../library/thorn_library_focused_thread_pool.hpp"
#include "../library/thorn_library_log_builder.hpp"
#include "../library/thorn_library_logger.hpp"
#include "../library/thorn_library_poster.hpp"
#include "../library/thorn_library_preprocessor.hpp"
#include "tcp/thorn_test_tcp_async_acceptor.hpp"
#include "tcp/thorn_test_tcp_async_connector.hpp"
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

void thorn_test_library_test_case_tcp_abstract_socket_holder(
    std::shared_ptr<thorn::library::tcp::abstract::socket_holder>
        pp_SocketHolderClass) {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  // NOTE: Object is valid
  BOOST_CHECK(pp_SocketHolderClass);

  // NOTE: Object is running from the start
  BOOST_CHECK(pp_SocketHolderClass->mf_is_running());

  // NOTE: mf_get_socket() call on a running object
  std::optional<boost::asio::ip::tcp::socket> lv_OptionalSocket{
      pp_SocketHolderClass->mf_get_socket()};

  BOOST_CHECK(lv_OptionalSocket);

  boost::system::error_code lv_ErrorCode{};
  lv_OptionalSocket->close(lv_ErrorCode);

  BOOST_CHECK(!lv_ErrorCode);

  lv_OptionalSocket.reset();

  // NOTE: Object is no longer running
  BOOST_CHECK(!pp_SocketHolderClass->mf_is_running());

  // NOTE: mf_get_socket() call on a non-running object
  BOOST_CHECK(!pp_SocketHolderClass->mf_get_socket());
};

BOOST_AUTO_TEST_CASE(thorn_test_library_test_case_acceptor) {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  boost::asio::io_context lv_Context{};

  constexpr std::string_view lc_Addres{"127.0.0.1"};
  constexpr std::uint16_t lc_Port{15051};

  thorn::test::tcp::async_connector lv_AsyncConnector{lc_Addres, lc_Port};

  // NOTE: We run the async_connector in parallel to make the acceptor work
  lv_AsyncConnector.mf_async_connect();

  std::shared_ptr<thorn::library::tcp::acceptor> lp_Acceptor{
      std::make_shared<thorn::library::tcp::acceptor>(lv_Context, lc_Port)};

  thorn_test_library_test_case_abstract_runnable(lp_Acceptor);

  // NOTE: Next test requires the acceptor to be running from the start
  lp_Acceptor->mf_run();

  thorn_test_library_test_case_tcp_abstract_socket_holder(lp_Acceptor);
}

BOOST_AUTO_TEST_CASE(thorn_test_library_test_case_connector) {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  boost::asio::io_context lv_Context{};

  constexpr std::string_view lc_Addres{"127.0.0.1"};
  constexpr std::uint16_t lc_Port{15052};

  thorn::test::tcp::async_acceptor lv_AsyncAcceptor{lc_Port};

  // NOTE: We run the async_acceptor in parallel to make the connector work
  lv_AsyncAcceptor.mf_async_accept();

  std::shared_ptr<thorn::library::tcp::connector> lp_Connector{
      std::make_shared<thorn::library::tcp::connector>(lv_Context, lc_Addres,
                                                       lc_Port)};

  thorn_test_library_test_case_abstract_runnable(lp_Connector);

  // NOTE: Next test requires the connector to be running from the start
  lp_Connector->mf_run();

  thorn_test_library_test_case_tcp_abstract_socket_holder(lp_Connector);
}

BOOST_AUTO_TEST_CASE(thorn_test_library_test_case_context) {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  std::shared_ptr<thorn::library::context> lp_Context{
      std::make_shared<thorn::library::context>()};

  thorn_test_library_test_case_abstract_runnable(lp_Context);

  // NOTE: Checking if the inner context is running
  lp_Context->mf_run();
  BOOST_CHECK(!lp_Context->mf_get_context().stopped());

  // NOTE: Checking if the inner context is stopped
  lp_Context->mf_stop();
  BOOST_CHECK(lp_Context->mf_get_context().stopped());
}

BOOST_AUTO_TEST_CASE(thorn_test_library_test_case_focused_thread_pool) {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  thorn_test_library_test_case_abstract_runnable(
      std::make_shared<thorn::library::focused_thread_pool>(
          []() noexcept -> void {}));
}

BOOST_AUTO_TEST_CASE(thorn_test_library_test_case_poster) {
  _THORN_LIBRARY_LOG_FUNCTION_CALL_();

  bool lv_Triggered{false};
  boost::asio::io_context lv_Context{};

  {
    thorn::library::poster lv_Poster{
        lv_Context,
        [&lv_Triggered]() noexcept -> void { lv_Triggered = true; }};
    // NOTE: Poster destructor will schedule work on context
  }

  lv_Context.run();
  BOOST_CHECK(lv_Triggered);
}

BOOST_AUTO_TEST_SUITE_END()
