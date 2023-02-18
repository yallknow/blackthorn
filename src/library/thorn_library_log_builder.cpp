#include "thorn_library_log_builder.hpp"

#include <thread>

#include "thorn_library_logger.hpp"
#include "thorn_library_time.hpp"

std::atomic<bool> thorn::library::log_builder::msv_IsNextSectionClosed{false};

thorn::library::log_builder::log_builder(
    const std::string_view pc_Name) noexcept
    : mc_StartTime{std::chrono::high_resolution_clock::now()} {
  const std::string lc_PID{
      std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()))};

  const std::string lc_Header{"{ \"time\": \"" + time::msf_now() +
                              "\", \"pid\":\"" + lc_PID + "\", \"name\": \"" +
                              pc_Name.data() + "\", \"next\": [ "};

  if (msv_IsNextSectionClosed) {
    logger::msf_log(", " + lc_Header);
  } else {
    logger::msf_log(lc_Header);
  }

  msv_IsNextSectionClosed = false;
}

thorn::library::log_builder::~log_builder() noexcept {
  const std::chrono::nanoseconds lc_Took{
      std::chrono::high_resolution_clock::now() - this->mc_StartTime};

  const std::string lc_Footer{
      " ], \"took(ns)\": " + std::to_string(lc_Took.count()) + " }"};

  logger::msf_log(lc_Footer);

  msv_IsNextSectionClosed = true;
}

void thorn::library::log_builder::msf_init() noexcept {
  logger::msf_init();

  if (logger::msf_is_initialized()) {
    logger::msf_log("[ ");
    logger::msf_async_log(
        "[ { \"time\": \"" + time::msf_now() +
        "\", \"pid\": \"0\", \"tag\": \"INFO\", \"value\": \"Start\" }");
  }
}

void thorn::library::log_builder::msf_destroy() noexcept {
  if (logger::msf_is_initialized()) {
    logger::msf_log(" ]");
    logger::msf_async_log(" ]");
  }

  logger::msf_destroy();
}

bool thorn::library::log_builder::msf_is_initialized() noexcept {
  return logger::msf_is_initialized();
}

void thorn::library::log_builder::msf_log(
    const std::string_view pc_Tag, const std::string_view pc_Message,
    const boost::system::error_code pc_ErrorCode) noexcept {
  const std::string lc_Body{msf_create_body(pc_Tag, pc_Message, pc_ErrorCode)};

  if (msv_IsNextSectionClosed) {
    logger::msf_log(", " + lc_Body);
  } else {
    logger::msf_log(lc_Body);
  }

  msv_IsNextSectionClosed = true;
}

void thorn::library::log_builder::msf_async_log(
    const std::string_view pc_Tag, const std::string_view pc_Message,
    const boost::system::error_code pc_ErrorCode) noexcept {
  const std::string lc_PID{
      std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()))};

  std::string lv_Record{", { \"time\": \"" + time::msf_now() +
                        "\", \"pid\": \"" + lc_PID.c_str() + "\", \"tag\": \"" +
                        pc_Tag.data() + "\", \"value\": \"" +
                        pc_Message.data()};

  if (pc_ErrorCode) {
    lv_Record += " (" + std::to_string(pc_ErrorCode.value()) + " : " +
                 pc_ErrorCode.what() + ")";
  }

  logger::msf_async_log(lv_Record + "\" }");
}

void thorn::library::log_builder::msf_set_log_directory(
    const std::string_view pc_LogDirectory) noexcept {
  thorn::library::logger::msf_set_log_directory(pc_LogDirectory);
}

void thorn::library::log_builder::msf_set_log_filename_prefix(
    const std::string_view pc_LogFilenamePrefix) noexcept {
  thorn::library::logger::msf_set_log_filename_prefix(pc_LogFilenamePrefix);
}

void thorn::library::log_builder::msf_set_log_filename_postfix(
    const std::string_view pc_LogFilenamePostfix) noexcept {
  thorn::library::logger::msf_set_log_filename_postfix(pc_LogFilenamePostfix);
}

std::string thorn::library::log_builder::msf_create_body(
    const std::string_view pc_Tag, const std::string_view pc_Message,
    const boost::system::error_code pc_ErrorCode) noexcept {
  std::string lv_Body{};

  lv_Body += "{ \"";
  lv_Body += pc_Tag;
  lv_Body += "\": \"";
  lv_Body += pc_Message;

  if (pc_ErrorCode) {
    lv_Body += " (" + std::to_string(pc_ErrorCode.value()) + " : " +
               pc_ErrorCode.what() + ")";
  }

  lv_Body += "\" }";

  return lv_Body;
}
