#pragma once

#include "Neat/Events/Events/MouseButtonEvent.hpp"

namespace Neat {

struct MouseButtonPressedEvent : public MouseButtonEvent {
  MouseButtonPressedEvent(Mouse button) : MouseButtonEvent(button) {}
};
}  // namespace Neat