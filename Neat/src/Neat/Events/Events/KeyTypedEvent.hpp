#pragma once

#include "Neat/Events/Events/KeyEvent.hpp"

namespace Neat {
struct KeyTypedEvent : public KeyEvent {
  KeyTypedEvent(Key key) : KeyEvent(key) {}
};
}  // namespace Neat