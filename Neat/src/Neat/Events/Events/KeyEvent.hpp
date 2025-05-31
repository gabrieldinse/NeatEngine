#pragma once

#include "Neat/Core/KeyCodes.hpp"

namespace Neat {
struct KeyEvent {
  Key key;

 protected:
  KeyEvent(Key key) : key(key) {}
};
}  // namespace Neat