#pragma once

#include <utility>

#include "Neat/Core/Core.h"
#include "Neat/Core/KeyCodes.h"
#include "Neat/Core/MouseCodes.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class Input
   {
   public:
      static bool isKeyPressed(KeyCode key);
      static bool isMouseButtonPressed(MouseCode button);
      static Vec2 getMousePosition();
      static float getMouseX();
      static float getMouseY();
   };
   
}