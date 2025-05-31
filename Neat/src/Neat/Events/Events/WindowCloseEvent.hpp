#pragma once

#include "Neat/Events/Events/WindowEvent.hpp"

namespace Neat {
struct WindowCloseEvent : public WindowEvent {
  WindowCloseEvent() = default;
};
}  // namespace Neat