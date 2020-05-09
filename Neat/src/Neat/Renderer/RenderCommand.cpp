#include "Neat/Renderer/RenderCommand.h"
#include "Neat/Debug/Instrumentator.h"

#include <glad/glad.h>


namespace Neat
{
   void RenderCommand::init()
   {
      NT_PROFILE_FUNCTION();

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      glEnable(GL_DEPTH_TEST);
   }

   void RenderCommand::setClearColor(const Vec4 color)
   {
      glClearColor(color.r, color.g, color.b, color.a);
   }

   void RenderCommand::clear()
   {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   }

   void RenderCommand::drawIndexed(
      const std::shared_ptr<VertexArray>& vertexArray, UInt indexCount)
   {
      UInt count = (indexCount == 0)
         ? vertexArray->getIndexBuffer()->getCount()
         : indexCount;

      glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
      glBindTexture(GL_TEXTURE_2D, 0);
   }

   void RenderCommand::setViewport(
      UInt xOffset, UInt yOffset, UInt width, UInt height)
   {
      glViewport(xOffset, yOffset, width, height);
   }
}