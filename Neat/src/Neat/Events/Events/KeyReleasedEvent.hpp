#pragma once

#include "Neat/Events/Events/KeyEvent.hpp"

namespace Neat {
struct KeyReleasedEvent : public KeyEvent {
  KeyReleasedEvent(Key key) : KeyEvent(key) {}
};
}  // namespace Neat