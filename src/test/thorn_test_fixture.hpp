#pragma once

#ifndef _THORN_TEST_FIXTURE_
#define _THORN_TEST_FIXTURE_

namespace thorn {
namespace test {

class fixture final {
 public:
  explicit fixture() noexcept;
  /* virtual */ ~fixture() noexcept;

 public:
  explicit fixture(const fixture& pcl_Other) noexcept = delete;
  explicit fixture(fixture&& pr_Other) noexcept = delete;

 public:
  fixture& operator=(const fixture& pcl_Other) noexcept = delete;
  fixture& operator=(fixture&& pr_Other) noexcept = delete;
};

}  // namespace test
}  // namespace thorn

#endif  // !_THORN_TEST_FIXTURE_
