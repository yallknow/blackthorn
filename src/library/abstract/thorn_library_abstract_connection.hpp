#pragma once

#ifndef _THORN_LIBRARY_ABSTRACT_CONNECTION_
#define _THORN_LIBRARY_ABSTRACT_CONNECTION_

namespace thorn {
namespace library {
namespace abstract {

class connection /* final */ {
 public:
  explicit connection() noexcept;
  virtual ~connection() noexcept;

 public:
  virtual void mpf_on_message() = 0;
  virtual void mpf_on_disconnect() = 0;

 public:
  explicit connection(const connection& pcl_Other) noexcept = delete;
  explicit connection(connection&& pr_Other) noexcept = delete;

 public:
  connection& operator=(const connection& pcl_Other) noexcept = delete;
  connection& operator=(connection&& pr_Other) noexcept = delete;
};

}  // namespace abstract
}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_ABSTRACT_CONNECTION_
