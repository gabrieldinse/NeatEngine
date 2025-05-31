#pragma once

#include "Neat/Events/Events/MouseEvent.hpp"

namespace Neat {

struct MouseScrolledEvent : public MouseEvent {
 public:
  MouseScrolledEvent(float xOffset, float yOffset)
      : xOffset(xOffset), yOffset(yOffset) {}

  float xOffset;
  float yOffset;
};
}  // namespace Neat