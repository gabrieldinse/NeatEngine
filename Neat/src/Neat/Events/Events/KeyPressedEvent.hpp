#pragma once

#include "Neat/Events/Events/KeyEvent.hpp"

namespace Neat {
struct KeyPressedEvent : public KeyEvent {
  KeyPressedEvent(Key key, Int32 repeatCount = 0)
      : KeyEvent(key), repeatCount(repeatCount) {}

  Int32 repeatCount;
};
}  // namespace Neat