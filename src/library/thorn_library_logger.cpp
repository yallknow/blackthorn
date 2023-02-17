#include "thorn_library_logger.hpp"

#include <filesystem>
#include <system_error>

#include "thorn_library_preprocessor.hpp"
#include "thorn_library_time.hpp"

#if defined(_THORN_LIBRARY_CONSOLE_LOGGING_ENABLED_) || \
    defined(_THORN_LIBRARY_ASYNC_CONSOLE_LOGGING_ENABLED_)

#include <iostream>

#endif  // defined(_THORN_LIBRARY_CONSOLE_LOGGING_ENABLED_) || \
        // defined(_THORN_LIBRARY_ASYNC_CONSOLE_LOGGING_ENABLED_)

std::atomic<bool> thorn::library::logger::msv_IsInitialized{false};

std::string thorn::library::logger::msv_LogDirectory{"log/"};
std::string thorn::library::logger::msv_LogFilenamePrefix{};
std::string thorn::library::logger::msv_LogFilenamePostfix{".json"};

std::unique_ptr<std::ofstream> thorn::library::logger::msp_LogStream{nullptr};
std::unique_ptr<std::ofstream> thorn::library::logger::msp_AsyncLogStream{
    nullptr};

std::unique_ptr<std::mutex> thorn::library::logger::msp_LogStreamMutex{nullptr};
std::unique_ptr<std::mutex> thorn::library::logger::msp_AsyncLogStreamMutex{
    nullptr};

void thorn::library::logger::msf_init() noexcept {
  if (msv_IsInitialized) {
#if _THORN_LIBRARY_CONSOLE_LOGGING_ENABLED_
    std::cerr << gsc_WarningTag << ": " << __FUNCSIG__
              << " - Logger is already initialized!\n";
#endif

    return;
  }

  std::error_code lv_ErrorCode{};

  if (!std::filesystem::exists(msv_LogDirectory, lv_ErrorCode)) {
    std::filesystem::create_directories(msv_LogDirectory, lv_ErrorCode);

    if (lv_ErrorCode) {
#if _THORN_LIBRARY_CONSOLE_LOGGING_ENABLED_
      std::cerr << gsc_ErrorTag << ": " << __FUNCSIG__ << " - "
                << lv_ErrorCode.value() << " : "
                << lv_ErrorCode.message() + '\n';
#endif

      return;
    }
  }

  const std::string lc_TimeNow{time::msf_now_underscore()};

  msp_LogStream.reset(new (std::nothrow) std::ofstream{
      std::string{{msv_LogDirectory + '/' + msv_LogFilenamePrefix + lc_TimeNow +
                   msv_LogFilenamePostfix}},
      std::ofstream::trunc});

  msp_AsyncLogStream.reset(new (std::nothrow) std::ofstream{
      std::string{msv_LogDirectory + '/' + msv_LogFilenamePrefix + lc_TimeNow +
                  msc_LogFilenameAsyncPostfix.data() + msv_LogFilenamePostfix},
      std::ofstream::trunc});

  msp_LogStreamMutex.reset(new (std::nothrow) std::mutex{});
  msp_AsyncLogStreamMutex.reset(new (std::nothrow) std::mutex{});

  if (!msp_LogStream || !msp_LogStream->is_open() || !msp_AsyncLogStream ||
      !msp_AsyncLogStream->is_open() || !msp_LogStreamMutex ||
      !msp_AsyncLogStreamMutex) {
#if _THORN_LIBRARY_CONSOLE_LOGGING_ENABLED_
    std::cerr << gsc_ErrorTag << ": " << __FUNCSIG__
              << " - Can't initialize logger!\n";
#endif

    return;
  }

  msv_IsInitialized = true;
}

void thorn::library::logger::msf_destroy() noexcept {
  if (!msv_IsInitialized) {
#if _THORN_LIBRARY_CONSOLE_LOGGING_ENABLED_
    std::cerr << gsc_WarningTag << ": " << __FUNCSIG__
              << " - Logger is already destroyed!\n";
#endif

    return;
  }

  msp_LogStream->close();
  msp_LogStream.reset();

  msp_AsyncLogStream->close();
  msp_AsyncLogStream.reset();

  msp_LogStreamMutex.reset();
  msp_AsyncLogStreamMutex.reset();

  msv_IsInitialized = false;
}

bool thorn::library::logger::msf_is_initialized() noexcept {
  return msv_IsInitialized;
}

void thorn::library::logger::msf_log(const std::string_view pc_Data) noexcept {
  if (!msv_IsInitialized) {
#if _THORN_LIBRARY_CONSOLE_LOGGING_ENABLED_
    std::cout << gsc_ErrorTag << ": " << __FUNCSIG__
              << " - Logger is already destroyed!\n";
#endif

    return;
  }

  const std::lock_guard<std::mutex> lc_LogStreamLock{*msp_LogStreamMutex};
  *msp_LogStream << pc_Data;

#if _THORN_LIBRARY_CONSOLE_LOGGING_ENABLED_
  std::cout << pc_Data;
#endif
}

void thorn::library::logger::msf_async_log(
    const std::string_view pc_Data) noexcept {
  if (!msv_IsInitialized) {
#if _THORN_LIBRARY_ASYNC_CONSOLE_LOGGING_ENABLED_
    std::cout << gsc_ErrorTag << ": " << __FUNCSIG__
              << " - Logger is already destroyed!\n";
#endif

    return;
  }

  const std::lock_guard<std::mutex> lc_AsyncLogStreamLock{
      *msp_AsyncLogStreamMutex};
  *msp_AsyncLogStream << pc_Data;

#if _THORN_LIBRARY_ASYNC_CONSOLE_LOGGING_ENABLED_
  std::cout << pc_Data;
#endif
}

void thorn::library::logger::msf_set_log_directory(
    const std::string_view pc_LogDirectory) noexcept {
  msv_LogDirectory = pc_LogDirectory;
}

void thorn::library::logger::msf_set_log_filename_prefix(
    const std::string_view pc_LogFilenamePrefix) noexcept {
  msv_LogFilenamePrefix = pc_LogFilenamePrefix;
}

void thorn::library::logger::msf_set_log_filename_postfix(
    const std::string_view pc_LogFilenamePostfix) noexcept {
  msv_LogFilenamePostfix = pc_LogFilenamePostfix;
}
