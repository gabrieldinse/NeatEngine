#pragma once

#include <memory>

#include "Neat/Math/Vector.h"
#include "Neat/Math/Matrix.h"
#include "Neat/Math/Transforms.h"
#include "Neat/Core/Input.h"
#include "Neat/Graphics/Shapes2D/Quad.h"


namespace Neat
{
   struct Transform2D
   {
      Transform2D(const Vector2& position) : position(position) {}

      Vector2 position;
   };


   struct Direction2D
   {
      Direction2D(const Vector2& direction) : direction(direction) {}

      Vector2 direction;
   };


   struct Renderable
   {
      Renderable(std::unique_ptr<Shape>&& shape) : shape(std::move(shape)) {}

      std::unique_ptr<Shape> shape;
   };
}