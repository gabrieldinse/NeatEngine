#pragma once

#include <utility>

#include "PlatformDetection.hpp"
#include "KeyCodes.hpp"
#include "MouseButtonCodes.hpp"
#include "Window.hpp"

#include "Math/Vector.hpp"

namespace Neat {
class Input {
 public:
  struct InputImpl;

 public:
  static void setWindow(Window &window);
  static bool isKeyPressed(Key key);
  static bool isMouseButtonPressed(MouseButton button);
  static Vector2F getMousePosition();
  static float getMouseX();
  static float getMouseY();

 private:
  static Scope<InputImpl> s_impl;
};

}  // namespace Neat