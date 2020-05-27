#pragma once

#include "Neat/Core/Types.h"
#include "Neat/Graphics/VertexArray.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class RenderCommand
   {
   public:
      static void init();

      static void setClearColor(const Vector4 color);
      static void clear();
      static void clearWithColor(const Vector4 color);

      static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray,
         UInt indexCount = 0);

      static void setViewport(
         UInt xOffset, UInt yOffset, UInt width, UInt height);
   };
}