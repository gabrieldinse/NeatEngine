#include "Neat/Graphics/VertexArray.h"
#include "Neat/Graphics/Renderer.h"

#include <glad/glad.h>


namespace Neat
{
   VertexArray::VertexArray()
   {
      glCreateVertexArrays(1, &m_id);
   }

   VertexArray::~VertexArray()
   {
      glDeleteVertexArrays(1, &m_id);
   }

   void VertexArray::bind() const
   {
      glBindVertexArray(m_id);
   }

   void VertexArray::unbind() const
   {
      glBindVertexArray(0);
   }

   void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
   {
      NT_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(),
         "VertexBuffer has no layout!");
      glBindVertexArray(m_id);
      vertexBuffer->bind();

      const auto& layout = vertexBuffer->getLayout();
      for (const auto& element : layout)
      {
         glEnableVertexAttribArray(element.index);
         glVertexAttribPointer(
            element.index,
            element.componentCount,
            element.dataType,
            element.normalized,
            layout.getOffset(),
            static_cast<const void*>(static_cast<const char*>(0) + element.offset));
      }

      m_vertexBuffers.push_back(vertexBuffer);
   }

   void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
   {
      glBindVertexArray(m_id);
      indexBuffer->bind();
      m_indexBuffer = indexBuffer;
   }
}