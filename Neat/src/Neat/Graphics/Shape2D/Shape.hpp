#pragma once

#include "Neat/Graphics/Renderer2D.hpp"


namespace Neat
{
   class Shape
   {
   public:
      Shape() = default;
      virtual ~Shape() = default;

      virtual void draw() const = 0;
   };
}