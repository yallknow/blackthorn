#pragma once

#ifndef _THORN_LIBRARY_MESSAGE_HEADER_
#define _THORN_LIBRARY_MESSAGE_HEADER_

#include <cstdint>

namespace thorn {
namespace library {

class message_header final {
 public:
  const std::uint16_t mc_Code{};
  const std::uint16_t mc_Flags{};
  const std::uint32_t mc_BodySize{};
};

}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_MESSAGE_HEADER_
