#pragma once

#include <memory>

#include "Neat/Math/Vector.h"
#include "Neat/Math/Matrix.h"
#include "Neat/Math/Transform.h"
#include "Neat/Core/Input.h"
#include "Neat/Graphics/Shape2D/Quad.h"


namespace Neat
{
   struct Transform2D
   {
      Transform2D(const Vector2F& position) : position(position) {}

      Vector2F position;
   };


   struct Direction2D
   {
      Direction2D(const Vector2F& direction) : direction(direction) {}

      Vector2F direction;
   };


   struct Renderable
   {
      Renderable(std::unique_ptr<Shape>&& shape) : shape(std::move(shape)) {}

      std::unique_ptr<Shape> shape;
   };
}