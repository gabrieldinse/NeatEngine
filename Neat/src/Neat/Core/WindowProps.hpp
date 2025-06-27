#pragma once

#include <string>

#include "Neat/Core/Types.hpp"
#include "Neat/Events/EventDispatcher.hpp"

namespace Neat {
class EventDispatcher;
struct WindowProps {
  std::string title;
  Int32 width;
  Int32 height;
  bool minimized = false;
  bool vSync = false;
  std::shared_ptr<EventDispatcher> eventDispatcher;

  WindowProps(const std::shared_ptr<EventDispatcher> &eventDispatcher,
              const std::string &title = "Neat Engine", Int32 width = 1280,
              Int32 height = 720)
      : eventDispatcher(eventDispatcher),
        title(title),
        width(width),
        height(height) {}
};
}  // namespace Neat