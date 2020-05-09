#include "Neat/Core/Input.h"
#include "Neat/Core/Application.h"
#include "Neat/Debug/Instrumentator.h"

#include <GLFW/glfw3.h>


namespace Neat
{
   Bool isKeyPressed(KeyCode key)
   {
      NT_PROFILE_FUNCTION();

      auto window = static_cast<GLFWwindow*>(
         Application::get().getWindow().getNativeWindow());
      auto state = glfwGetKey(window, static_cast<Int>(key));
      return (state == GLFW_PRESS || state == GLFW_REPEAT);
   }

   Bool isMouseButtonPressed(MouseCode button)
   {
      NT_PROFILE_FUNCTION();

      auto window = static_cast<GLFWwindow*>(
         Application::get().getWindow().getNativeWindow());
      auto state = glfwGetMouseButton(window, static_cast<Int>(button));
      return (state == GLFW_PRESS);
   }

   Vec2 getMousePosition()
   {
      NT_PROFILE_FUNCTION();

      auto window = static_cast<GLFWwindow*>(
         Application::get().getWindow().getNativeWindow());
      Double xPos, yPos;
      glfwGetCursorPos(window, &xPos, &yPos);
      return { (Float)xPos, (Float)yPos };
   }

   Float getMouseX()
   {
      NT_PROFILE_FUNCTION();

      return getMousePosition().x;
   }

   Float getMouseY()
   {
      NT_PROFILE_FUNCTION();

      return getMousePosition().y;
   }
}