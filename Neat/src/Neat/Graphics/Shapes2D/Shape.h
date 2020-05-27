#pragma once

#include "Neat/Graphics/Renderer2D.h"


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