#pragma once

#include "Neat/Events/Events/MouseEvent.hpp"

namespace Neat {

struct MouseMovedEvent : public MouseEvent {
  MouseMovedEvent(float xPos, float yPos) : xPos(xPos), yPos(yPos) {}

  float xPos;
  float yPos;
};
}  // namespace Neat