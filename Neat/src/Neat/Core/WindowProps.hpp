#pragma once

#include <string>

#include "Neat/Core/Types.hpp"
#include "Neat/Events/EventManager.hpp"

namespace Neat {
class EventManager;
struct WindowProps {
  std::string title;
  Int32 width;
  Int32 height;
  bool minimized = false;
  bool vSync = false;
  std::shared_ptr<EventManager> eventManager;

  WindowProps(const std::shared_ptr<EventManager> &eventManager,
              const std::string &title = "Neat Engine", Int32 width = 1280,
              Int32 height = 720)
      : eventManager(eventManager),
        title(title),
        width(width),
        height(height) {}
};
}  // namespace Neat