#pragma once

#ifndef _THORN_LIBRARY_STRING_CAST_
#define _THORN_LIBRARY_STRING_CAST_

#include <sstream>
#include <string>
#include <string_view>

#include "thorn_library_preprocessor.hpp"

namespace thorn {
namespace library {

template <typename T>
class string_cast final {
 public:
  static T msf_make_value(const std::string_view pc_String) noexcept;
  static std::string msf_make_string(const T& pcl_Value) noexcept;

 public:
  explicit string_cast() noexcept = delete;
  /* virtual */ ~string_cast() noexcept = delete;

 public:
  explicit string_cast(const string_cast& pcl_Other) noexcept = delete;
  explicit string_cast(string_cast&& pr_Other) noexcept = delete;

 public:
  string_cast& operator=(const string_cast& pcl_Other) noexcept = delete;
  string_cast& operator=(string_cast&& pr_Other) noexcept = delete;
};

template <typename T>
T string_cast<T>::msf_make_value(const std::string_view pc_String) noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  // NOTE: The T type must have a default and copy (or move) constructors
  T lv_Value{};

  std::istringstream lv_InStream{
      {pc_String.data(), pc_String.data() + sizeof(T)}};

  lv_InStream.read((char*)&lv_Value, sizeof(T));

  return lv_Value;
}

template <typename T>
std::string string_cast<T>::msf_make_string(const T& pcl_Value) noexcept {
  _THORN_LIBRARY_ASYNC_LOG_FUNCTION_CALL_();

  std::ostringstream lv_OutStream{};

  lv_OutStream.write((char*)&pcl_Value, sizeof(T));

  return lv_OutStream.str();
}

}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_STRING_CAST_
