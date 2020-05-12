#pragma once

#include "Neat/Core/Types.h"
#include "Neat/Renderer/Buffer.h"


namespace Neat
{
   class VertexArray
   {
   public:
      VertexArray();
      ~VertexArray();
      void bind() const;
      void unbind() const;

      void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
      void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

      const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const
      {
         return this->vertexBuffers;
      }

      const std::shared_ptr<IndexBuffer>& getIndexBuffer() const
      {
         return this->indexBuffer;
      }

   private:
      UInt id = 0;
      std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
      std::shared_ptr<IndexBuffer> indexBuffer;
   };
}