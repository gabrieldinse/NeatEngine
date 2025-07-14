#include "NeatPCH.hpp"

#include "Neat/Core/Application.hpp"
#include "Neat/Core/Input.hpp"

#include <GLFW/glfw3.h>

namespace Neat {
Scope<Input::InputImpl> Input::s_impl;

struct Input::InputImpl {
  InputImpl(GLFWwindow *window) : window(window) {}

  GLFWwindow *window;
};

void Input::setWindow(Window &window) {
  s_impl =
      makeScope<InputImpl>(static_cast<GLFWwindow *>(window.getNativeWindow()));
}

bool Input::isKeyPressed(Key key) {
  auto state = glfwGetKey(s_impl->window, enumToInt(key));

  return (state == GLFW_PRESS or state == GLFW_REPEAT);
}

bool Input::isMouseButtonPressed(MouseButton button) {
  auto state = glfwGetMouseButton(s_impl->window, enumToInt(button));

  return (state == GLFW_PRESS);
}

Vector2F Input::getMousePosition() {
  double xPos, yPos;
  glfwGetCursorPos(s_impl->window, &xPos, &yPos);

  return {(float)xPos, (float)yPos};
}

float Input::getMouseX() { return getMousePosition().x; }

float Input::getMouseY() { return getMousePosition().y; }
}  // namespace Neat