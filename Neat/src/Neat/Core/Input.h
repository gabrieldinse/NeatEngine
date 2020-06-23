#pragma once

#include <utility>

#include "Neat/Core/Base.h"
#include "Neat/Core/Window.h"
#include "Neat/Core/KeyCodes.h"
#include "Neat/Core/MouseCodes.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class Input
   {
   public:
      struct InputImpl;

   public:
      static void setWindow(Window& window);
      static bool isKeyPressed(KeyCode key);
      static bool isMouseButtonPressed(MouseCode button);
      static Vector2F getMousePosition();
      static float getMouseX();
      static float getMouseY();

   private:
      static std::unique_ptr<InputImpl> s_data;
   };
   
}