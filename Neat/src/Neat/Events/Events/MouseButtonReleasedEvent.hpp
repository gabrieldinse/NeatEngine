#pragma once

#include "Neat/Events/Events/MouseButtonEvent.hpp"

namespace Neat {
struct MouseButtonReleasedEvent : public MouseButtonEvent {
  MouseButtonReleasedEvent(Mouse button) : MouseButtonEvent(button) {}
};
}  // namespace Neat