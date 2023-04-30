#pragma once

#ifndef _THORN_LIBRARY_PREPROCESSOR_
#define _THORN_LIBRARY_PREPROCESSOR_

#ifndef _THORN_LIBRARY_PROFILING_ENABLED_
#define _THORN_LIBRARY_PROFILING_ENABLED_ 0
#endif  // !_THORN_LIBRARY_PROFILING_ENABLED_

#ifndef _THORN_LIBRARY_LOGGING_ENABLED_
#define _THORN_LIBRARY_LOGGING_ENABLED_ 0
#endif  // !_THORN_LIBRARY_LOGGING_ENABLED_

#ifndef _THORN_LIBRARY_ASYNC_LOGGING_ENABLED_
#define _THORN_LIBRARY_ASYNC_LOGGING_ENABLED_ 0
#endif  // !_THORN_LIBRARY_ASYNC_LOGGING_ENABLED_

#if _THORN_LIBRARY_PROFILING_ENABLED_ || _THORN_LIBRARY_LOGGING_ENABLED_ || \
    _THORN_LIBRARY_ASYNC_LOGGING_ENABLED_

#ifndef __FUNCSIG__
#define __FUNCSIG__ __PRETTY_FUNCTION__
#endif  //!__FUNCSIG__

#endif  // _THORN_LIBRARY_PROFILING_ENABLED_ || _THORN_LIBRARY_LOGGING_ENABLED_
        // || _THORN_LIBRARY_ASYNC_LOGGING_ENABLED_

#if _THORN_LIBRARY_PROFILING_ENABLED_

#include "thorn_library_scope_profiler.hpp"

#define _THORN_LIBRARY_PROFILE_FUNCTION_() \
  const thorn::library::scope_profiler lc_ScopeProfiler(__FUNCSIG__)

#else

#define _THORN_LIBRARY_PROFILE_FUNCTION_()

#endif  // _THORN_LIBRARY_PROFILING_ENABLED_

#if _THORN_LIBRARY_LOGGING_ENABLED_ || _THORN_LIBRARY_ASYNC_LOGGING_ENABLED_

#include <boost/system/error_code.hpp>
#include <string_view>

#include "thorn_library_log_builder.hpp"

static constexpr std::string_view gsc_InfoTag{"INFO"};
static constexpr std::string_view gsc_WarningTag{"WARNING"};
static constexpr std::string_view gsc_ErrorTag{"ERROR"};

#endif  // _THORN_LIBRARY_LOGGING_ENABLED_ ||
        // _THORN_LIBRARY_ASYNC_LOGGING_ENABLED_

#if _THORN_LIBRARY_LOGGING_ENABLED_

#if _THORN_LIBRARY_PROFILING_ENABLED_

#define _THORN_LIBRARY_LOG_FUNCTION_CALL_()                     \
  const thorn::library::log_builder lc_LogBuilder(__FUNCSIG__); \
  _THORN_LIBRARY_PROFILE_FUNCTION_()

#else

#define _THORN_LIBRARY_LOG_FUNCTION_CALL_() \
  const thorn::library::log_builder lc_LogBuilder(__FUNCSIG__)

#endif  // _THORN_LIBRARY_PROFILING_ENABLED_

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

#if _THORN_LIBRARY_PROFILING_ENABLED_

#define _THORN_LIBRARY_LOG_FUNCTION_CALL_() _THORN_LIBRARY_PROFILE_FUNCTION_()

#else

#define _THORN_LIBRARY_LOG_FUNCTION_CALL_()

#endif  // _THORN_LIBRARY_PROFILING_ENABLED_

#define _THORN_LIBRARY_LOG_INFO_(pc_Message)
#define _THORN_LIBRARY_LOG_WARNING_(pc_Message)
#define _THORN_LIBRARY_LOG_ERROR_(pc_Message)
#define _THORN_LIBRARY_LOG_ERROR_CODE_(pc_Message, pc_ErrorCode)

#endif  // _THORN_LIBRARY_LOGGING_ENABLED_

#if _THORN_LIBRARY_ASYNC_LOGGING_ENABLED_

#if _THORN_LIBRARY_PROFILING_ENABLED_

#define _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_()                          \
  thorn::library::log_builder::msf_async_log(gsc_InfoTag, __FUNCSIG__,     \
                                             boost::system::error_code{}); \
  _THORN_LIBRARY_PROFILE_FUNCTION_()

#else

#define _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_()                      \
  thorn::library::log_builder::msf_async_log(gsc_InfoTag, __FUNCSIG__, \
                                             boost::system::error_code{})

#endif  // _THORN_LIBRARY_PROFILING_ENABLED_

#define _THORN_LIBRARY_ASYNC_LOG_INFO_(pc_Message)                \
  thorn::library::log_builder::msf_async_log(                     \
      gsc_InfoTag, std::string{__FUNCSIG__} + " : " + pc_Message, \
      boost::system::error_code{})

#define _THORN_LIBRARY_ASYNC_LOG_WARNING_(pc_Message)                \
  thorn::library::log_builder::msf_async_log(                        \
      gsc_WarningTag, std::string{__FUNCSIG__} + " : " + pc_Message, \
      boost::system::error_code{})

#define _THORN_LIBRARY_ASYNC_LOG_ERROR_(pc_Message)                \
  thorn::library::log_builder::msf_async_log(                      \
      gsc_ErrorTag, std::string{__FUNCSIG__} + " : " + pc_Message, \
      boost::system::error_code{})

#define _THORN_LIBRARY_ASYNC_LOG_ERROR_CODE_(pc_Message, pc_ErrorCode) \
  thorn::library::log_builder::msf_async_log(                          \
      gsc_ErrorTag, std::string{__FUNCSIG__} + " : " + pc_Message,     \
      pc_ErrorCode)

#else

#if _THORN_LIBRARY_PROFILING_ENABLED_

#define _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_() \
  _THORN_LIBRARY_PROFILE_FUNCTION_()

#else

#define _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_()

#endif  // _THORN_LIBRARY_PROFILING_ENABLED_

#define _THORN_LIBRARY_ASYNC_LOG_INFO_(pc_Message)
#define _THORN_LIBRARY_ASYNC_LOG_WARNING_(pc_Message)
#define _THORN_LIBRARY_ASYNC_LOG_ERROR_(pc_Message)
#define _THORN_LIBRARY_ASYNC_LOG_ERROR_CODE_(pc_Message, pc_ErrorCode)

#endif  // _THORN_LIBRARY_ASYNC_LOGGING_ENABLED_

#endif  // !_THORN_LIBRARY_PREPROCESSOR_
