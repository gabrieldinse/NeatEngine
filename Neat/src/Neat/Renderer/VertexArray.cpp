#include "VertexArray.h"
#include "Renderer.h"
#include "Neat/Debug/Instrumentator.h"

#include <glad/glad.h>


namespace Neat
{
   VertexArray::VertexArray()
   {
      NT_PROFILE_FUNCTION();

      glCreateVertexArrays(1, &m_id);
   }

   VertexArray::~VertexArray()
   {
      NT_PROFILE_FUNCTION();

      glDeleteVertexArrays(1, &m_id);
   }

   void VertexArray::bind() const
   {
      NT_PROFILE_FUNCTION();

      glBindVertexArray(m_id);
   }

   void VertexArray::unbind() const
   {
      NT_PROFILE_FUNCTION();

      glBindVertexArray(0);
   }

   void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
   {
      NT_PROFILE_FUNCTION();

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
            layout.getStride(),
            static_cast<const void*>(static_cast<const char*>(0) + element.offset));
      }

      m_vertexBuffers.push_back(vertexBuffer);
   }

   void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
   {
      NT_PROFILE_FUNCTION();

      glBindVertexArray(m_id);
      indexBuffer->bind();
      m_indexBuffer = indexBuffer;
   }
}