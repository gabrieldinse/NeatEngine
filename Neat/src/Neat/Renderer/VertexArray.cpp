#include "VertexArray.h"
#include "Renderer.h"
#include "Neat/Debug/Instrumentator.h"

#include <glad/glad.h>


namespace Neat
{
   VertexArray::VertexArray()
   {
      NT_PROFILE_FUNCTION();

      glCreateVertexArrays(1, &this->rendererID);
   }

   VertexArray::~VertexArray()
   {
      NT_PROFILE_FUNCTION();

      glDeleteVertexArrays(1, &this->rendererID);
   }

   void VertexArray::bind() const
   {
      NT_PROFILE_FUNCTION();

      glBindVertexArray(this->rendererID);
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
      glBindVertexArray(this->rendererID);
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
            static_cast<const void*>(static_cast<const Char*>(0) + element.offset));
      }

      this->vertexBuffers.push_back(vertexBuffer);
   }

   void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
   {
      NT_PROFILE_FUNCTION();

      glBindVertexArray(this->rendererID);
      indexBuffer->bind();
      this->indexBuffer = indexBuffer;
   }
}