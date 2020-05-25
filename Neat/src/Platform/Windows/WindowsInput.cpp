#include <memory>

#include "Neat/Core/Input.h"
#include "Neat/Core/Application.h"

#include <GLFW/glfw3.h>


namespace Neat
{
   struct Input::InputImpl
   {
      InputImpl(GLFWwindow* window) : window(window) {}

      GLFWwindow* window;
   };

   std::unique_ptr<Input::InputImpl> Input::s_data;

   void Input::init(void* window)
   {
      s_data = std::make_unique<InputImpl>(static_cast<GLFWwindow*>(window));
   }

   bool Input::isKeyPressed(KeyCode key)
   {
      auto state = glfwGetKey(s_data->window, static_cast<Int>(key));
      return (state == GLFW_PRESS || state == GLFW_REPEAT);
   }

   bool Input::isMouseButtonPressed(MouseCode button)
   {
      auto state = glfwGetMouseButton(s_data->window, static_cast<Int>(button));
      return (state == GLFW_PRESS);
   }

   Vector2 Input::getMousePosition()
   {
      double xPos, yPos;
      glfwGetCursorPos(s_data->window, &xPos, &yPos);
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