#pragma once

#include "Core/KeyCodes.hpp"

namespace Neat {
struct KeyPressedEvent {
  Key key;
  Int32 repeatCount = 0;
};
}  // namespace Neat