#pragma once

#ifndef _THORN_LIBRARY_TCP_ABSTRACT_COMMUNICATOR_HOLDER_
#define _THORN_LIBRARY_TCP_ABSTRACT_COMMUNICATOR_HOLDER_

namespace thorn {
namespace library {
namespace tcp {
namespace abstract {

class communicator_holder /* final */ {
 public:
  explicit communicator_holder() noexcept;
  virtual ~communicator_holder() noexcept;

 public:
  virtual void mpf_on_disconnect() noexcept = 0;
  virtual void mpf_on_message() noexcept = 0;

 public:
  explicit communicator_holder(const communicator_holder& pcl_Other) noexcept =
      delete;
  explicit communicator_holder(communicator_holder&& pr_Other) noexcept =
      delete;

 public:
  communicator_holder& operator=(
      const communicator_holder& pcl_Other) noexcept = delete;
  communicator_holder& operator=(communicator_holder&& pr_Other) noexcept =
      delete;
};

}  // namespace abstract
}  // namespace tcp
}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_TCP_ABSTRACT_COMMUNICATOR_HOLDER_
