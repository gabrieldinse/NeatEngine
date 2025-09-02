#pragma once

namespace Neat {
class ImGuiRender {
 public:
  static void initialize();
  static void shutdown();
  static void begin();
  static void end();

 private:
  static void setFontsAndColorTheme();
};
}  // namespace Neat