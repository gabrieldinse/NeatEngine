#pragma once

#include <utility>

#include "Neat/Core/Base.hpp"
#include "Neat/Core/KeyCodes.hpp"
#include "Neat/Core/MouseButtonCodes.hpp"
#include "Neat/Core/Window.hpp"
#include "Neat/Math/Vector.hpp"

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
  static std::unique_ptr<InputImpl> s_impl;
};

}  // namespace Neat