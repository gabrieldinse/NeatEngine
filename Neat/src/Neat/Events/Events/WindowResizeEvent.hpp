#pragma once

#include "Neat/Events/Events/WindowEvent.hpp"
#include "Neat/Core/Types.hpp"

namespace Neat {
struct WindowResizeEvent : public WindowEvent {
  WindowResizeEvent(UInt32 width, UInt32 height)
      : width(width), height(height) {}

  UInt32 width;
  UInt32 height;
};
}  // namespace Neat