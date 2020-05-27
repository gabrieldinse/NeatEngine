#pragma once

#include "Neat/Core/Types.h"
#include "Neat/Graphics/Buffers.h"


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
         return m_vertexBuffers;
      }

      const std::shared_ptr<IndexBuffer>& getIndexBuffer() const
      {
         return m_indexBuffer;
      }

   private:
      UInt m_id = 0;
      std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
      std::shared_ptr<IndexBuffer> m_indexBuffer;
   };
}