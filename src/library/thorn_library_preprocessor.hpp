#pragma once

#ifndef _THORN_LIBRARY_PREPROCESSOR_
#define _THORN_LIBRARY_PREPROCESSOR_

#ifndef _THORN_LIBRARY_LOGGING_ENABLED_
#define _THORN_LIBRARY_LOGGING_ENABLED_ 1
#endif  // !_THORN_LIBRARY_LOGGING_ENABLED_

#ifndef _THORN_LIBRARY_ASYNC_LOGGING_ENABLED_
#define _THORN_LIBRARY_ASYNC_LOGGING_ENABLED_ 1
#endif  // !_THORN_LIBRARY_ASYNC_LOGGING_ENABLED_

#if defined(_THORN_LIBRARY_LOGGING_ENABLED_) || \
    defined(_THORN_LIBRARY_ASYNC_LOGGING_ENABLED_)

#ifndef _THORN_LIBRARY_CONSOLE_LOGGING_ENABLED_
#define _THORN_LIBRARY_CONSOLE_LOGGING_ENABLED_ 1
#endif  // !_THORN_LIBRARY_CONSOLE_LOGGING_ENABLED_

#ifndef _THORN_LIBRARY_ASYNC_CONSOLE_LOGGING_ENABLED_
#define _THORN_LIBRARY_ASYNC_CONSOLE_LOGGING_ENABLED_ 1
#endif  // !_THORN_LIBRARY_ASYNC_CONSOLE_LOGGING_ENABLED_

#include <boost/system/error_code.hpp>
#include <string_view>

#include "thorn_library_log_builder.hpp"

static constexpr std::string_view gsc_InfoTag{"INFO"};
static constexpr std::string_view gsc_WarningTag{"WARNING"};
static constexpr std::string_view gsc_ErrorTag{"ERROR"};

#endif  // defined(_THORN_LIBRARY_LOGGING_ENABLED_) || \
        // defined(_THORN_LIBRARY_ASYNC_LOGGING_ENABLED_)

#ifdef _THORN_LIBRARY_LOGGING_ENABLED_

#define _THORN_LIBRARY_LOG_FUNCTION_CALL_() \
  const thorn::library::log_builder lc_LogBuilder(__FUNCSIG__)

#define _THORN_LIBRARY_LOG_INFO_(pc_Message)                    \
  thorn::library::log_builder::msf_log(gsc_InfoTag, pc_Message, \
                                       boost::system::error_code{})

#define _THORN_LIBRARY_LOG_WARNING_(pc_Message)                    \
  thorn::library::log_builder::msf_log(gsc_WarningTag, pc_Message, \
                                       boost::system::error_code{})

#define _THORN_LIBRARY_LOG_ERROR_(pc_Message)                    \
  thorn::library::log_builder::msf_log(gsc_ErrorTag, pc_Message, \
                                       boost::system::error_code{})

#define _THORN_LIBRARY_LOG_ERROR_CODE_(pc_Message, pc_ErrorCode) \
  thorn::library::log_builder::msf_log(gsc_ErrorTag, pc_Message, pc_ErrorCode)

#else
#define _THORN_LIBRARY_LOG_FUNCTION_CALL_()
#define _THORN_LIBRARY_LOG_INFO_(pc_Message)
#define _THORN_LIBRARY_LOG_WARNING_(pc_Message)
#define _THORN_LIBRARY_LOG_ERROR_(pc_Message)
#define _THORN_LIBRARY_LOG_ERROR_CODE_(pc_Message, pc_ErrorCode)
#endif  // !_THORN_LIBRARY_LOGGING_ENABLED_

#if _THORN_LIBRARY_ASYNC_LOGGING_ENABLED_

#define _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_()                      \
  thorn::library::log_builder::msf_async_log(gsc_InfoTag, __FUNCSIG__, \
                                             boost::system::error_code{})

#define _THORN_LIBRARY_ASYNC_LOG_INFO_(pc_Message)                    \
  thorn::library::log_builder::msf_async_log(gsc_InfoTag, pc_Message, \
                                             boost::system::error_code{})

#define _THORN_LIBRARY_ASYNC_LOG_WARNING_(pc_Message)                    \
  thorn::library::log_builder::msf_async_log(gsc_WarningTag, pc_Message, \
                                             boost::system::error_code{})

#define _THORN_LIBRARY_ASYNC_LOG_ERROR_(pc_Message)                    \
  thorn::library::log_builder::msf_async_log(gsc_ErrorTag, pc_Message, \
                                             boost::system::error_code{})

#define _THORN_LIBRARY_ASYNC_LOG_ERROR_CODE_(pc_Message, pc_ErrorCode) \
  thorn::library::log_builder::msf_async_log(gsc_ErrorTag, pc_Message, \
                                             pc_ErrorCode)

#else
#define _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_()
#define _THORN_LIBRARY_ASYNC_LOG_INFO_(pc_Message)
#define _THORN_LIBRARY_ASYNC_LOG_WARNING_(pc_Message)
#define _THORN_LIBRARY_ASYNC_LOG_ERROR_(pc_Message)
#define _THORN_LIBRARY_ASYNC_LOG_ERROR_CODE_(pc_Message, pc_ErrorCode)
#endif  // !_THORN_LIBRARY_ASYNC_LOGGING_ENABLED_

#endif  // !_THORN_LIBRARY_PREPROCESSOR_
