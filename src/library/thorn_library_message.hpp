#pragma once

#ifndef _THORN_LIBRARY_MESSAGE_
#define _THORN_LIBRARY_MESSAGE_

#include <string>

#include "thorn_library_message_header.hpp"

namespace thorn {
namespace library {

class message final {
 public:
  const message_header mc_Header{};

 public:
  std::string mv_Body{};
};

}  // namespace library
}  // namespace thorn

#endif  // !_THORN_LIBRARY_MESSAGE_
