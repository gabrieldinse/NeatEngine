#pragma once

#include <utility>

#include "Neat/Core/Core.h"
#include "Neat/Core/KeyCodes.h"
#include "Neat/Core/MouseCodes.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   Bool isKeyPressed(KeyCode key);
   Bool isMouseButtonPressed(MouseCode button);
   Vec2 getMousePosition();
   Float getMouseX();
   Float getMouseY();
}