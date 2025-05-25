#pragma once

#include <utility>

#include "Neat/Core/Base.hpp"
#include "Neat/Core/KeyCodes.hpp"
#include "Neat/Core/MouseCodes.hpp"
#include "Neat/Core/Window.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
class Input {
public:
  struct InputImpl;

public:
  static void setWindow(Window &window);
  static bool isKeyPressed(KeyCode key);
  static bool isMouseButtonPressed(MouseCode button);
  static Vector2F getMousePosition();
  static float getMouseX();
  static float getMouseY();

private:
  static std::unique_ptr<InputImpl> s_impl;
};

} // namespace Neat