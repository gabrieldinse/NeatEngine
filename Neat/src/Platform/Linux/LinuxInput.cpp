#include <memory>

#include "Neat/Core/Input.hpp"
#include "Neat/Core/Application.hpp"

#include <GLFW/glfw3.h>

namespace Neat
{
   std::unique_ptr<Input::InputImpl> Input::s_impl;


   struct Input::InputImpl
   {
      InputImpl(GLFWwindow* window) : window(window) {}

      GLFWwindow* window;
   };

   void Input::setWindow(Window& window)
   {
      s_impl = std::make_unique<InputImpl>(
         static_cast<GLFWwindow*>(window.getNativeWindow()));
   }

   bool Input::isKeyPressed(KeyCode key)
   {
      auto state = glfwGetKey(s_impl->window, static_cast<Int32>(key));

      return (state == GLFW_PRESS || state == GLFW_REPEAT);
   }

   bool Input::isMouseButtonPressed(MouseCode button)
   {
      auto state = glfwGetMouseButton(s_impl->window, static_cast<Int32>(button));

      return (state == GLFW_PRESS);
   }

   Vector2F Input::getMousePosition()
   {
      double xPos, yPos;
      glfwGetCursorPos(s_impl->window, &xPos, &yPos);

      return { (float)xPos, (float)yPos };
   }

   float Input::getMouseX()
   {
      return getMousePosition().x;
   }

   float Input::getMouseY()
   {
      return getMousePosition().y;
   }
}