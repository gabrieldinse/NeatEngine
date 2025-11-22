#include "NeatPCH.hpp"

#include "Core/Input.hpp"

#include <GLFW/glfw3.h>

namespace Neat {
GLFWwindow *Input::s_window;

void Input::setWindow(Window &window) { s_window = window.getNativeWindow(); }

bool Input::isKeyPressed(Key key) {
  auto state = glfwGetKey(s_window, enumToInt(key));

  return (state == GLFW_PRESS or state == GLFW_REPEAT);
}

bool Input::isMouseButtonPressed(MouseButton button) {
  auto state = glfwGetMouseButton(s_window, enumToInt(button));

  return (state == GLFW_PRESS);
}

Vector2F Input::getMousePosition() {
  double xPos, yPos;
  glfwGetCursorPos(s_window, &xPos, &yPos);

  return {(float)xPos, (float)yPos};
}

float Input::getMouseX() { return getMousePosition().x(); }

float Input::getMouseY() { return getMousePosition().y(); }
}  // namespace Neat