#pragma once

#include "Neat/Events/Events/MouseEvent.hpp"
#include "Neat/Core/MouseCodes.hpp"

namespace Neat {
struct MouseButtonEvent : public MouseEvent {
  Mouse button;

 protected:
  MouseButtonEvent(Mouse button) : button(button) {}
};
}  // namespace Neat