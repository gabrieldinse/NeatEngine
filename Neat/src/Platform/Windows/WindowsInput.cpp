#include "Neat/Core/Input.h"
#include "Neat/Core/Application.h"
#include "Neat/Debug/Instrumentator.h"

#include <GLFW/glfw3.h>


namespace Neat
{

   bool Input::isKeyPressed(KeyCode key)
   {
      NT_PROFILE_FUNCTION();

      auto window = static_cast<GLFWwindow*>(
         Application::get().getWindow().getNativeWindow());
      auto state = glfwGetKey(window, static_cast<Int>(key));
      return (state == GLFW_PRESS || state == GLFW_REPEAT);
   }

   bool Input::isMouseButtonPressed(MouseCode button)
   {
      NT_PROFILE_FUNCTION();

      auto window = static_cast<GLFWwindow*>(
         Application::get().getWindow().getNativeWindow());
      auto state = glfwGetMouseButton(window, static_cast<Int>(button));
      return (state == GLFW_PRESS);
   }

   Vec2 Input::getMousePosition()
   {
      NT_PROFILE_FUNCTION();

      auto window = static_cast<GLFWwindow*>(
         Application::get().getWindow().getNativeWindow());
      double xPos, yPos;
      glfwGetCursorPos(window, &xPos, &yPos);
      return { (float)xPos, (float)yPos };
   }

   float Input::getMouseX()
   {
      NT_PROFILE_FUNCTION();

      return getMousePosition().x;
   }

   float Input::getMouseY()
   {
      NT_PROFILE_FUNCTION();

      return getMousePosition().y;
   }
}