#pragma once

#ifndef _THORN_TEST_FIXTURE_
#define _THORN_TEST_FIXTURE_

namespace thorn {
namespace test {

struct fixture final {
  explicit fixture() noexcept;
  /* virtual */ ~fixture() noexcept;
};

}  // namespace test
}  // namespace thorn

#endif  // !_THORN_TEST_FIXTURE_
