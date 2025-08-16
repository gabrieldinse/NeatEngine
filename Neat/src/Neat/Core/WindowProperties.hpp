#pragma once

#include <string>

#include "Neat/Core/Types.hpp"

namespace Neat {
class EventDispatcher;
struct WindowProperties {
  std::string title;
  Int32 width;
  Int32 height;
  bool minimized;
  bool vSync;

  WindowProperties(const std::string &title = "Neat Engine", Int32 width = 1280,
                   Int32 height = 720, bool minimized = false,
                   bool vSync = false)
      : title(title),
        width(width),
        height(height),
        minimized(minimized),
        vSync(vSync) {}
};
}  // namespace Neat