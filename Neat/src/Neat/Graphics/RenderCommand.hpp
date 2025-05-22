#pragma once

#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/VertexArray.hpp"
#include "Neat/Math/Vector.hpp"


namespace Neat
{
   class RenderCommand
   {
   public:
      static void init();

      static void setClearColor(const Vector4F color);
      static void clear();
      static void clearWithColor(const Vector4F color);

      static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray,
         UInt32 indexCount = 0);

      static void setViewport(
         UInt32 xOffset, UInt32 yOffset, UInt32 width, UInt32 height);
   };
}