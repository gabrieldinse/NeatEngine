#pragma once

namespace Neat {
class ImGuiRender {
 public:
  static void init();
  static void shutdown();
  static void begin();
  static void end();
};
}  // namespace Neat