#pragma once

#include <string>

#include "Neat/Core/Types.hpp"
#include "Neat/Events/EventDispatcher.hpp"

namespace Neat {
class EventDispatcher;
struct WindowProps {
  std::shared_ptr<EventDispatcher> eventDispatcher;
  std::string title;
  Int32 width;
  Int32 height;
  bool minimized;
  bool vSync;

  WindowProps(const std::shared_ptr<EventDispatcher> &eventDispatcher,
              const std::string &title = "Neat Engine", Int32 width = 1280,
              Int32 height = 720, bool minimized = false, bool vSync = false)
      : eventDispatcher(eventDispatcher),
        title(title),
        width(width),
        height(height),
        minimized(minimized),
        vSync(vSync) {}
};
}  // namespace Neat