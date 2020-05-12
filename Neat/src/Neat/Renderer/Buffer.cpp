#include "Neat/Renderer/Buffer.h"
#include "Neat/Debug/Instrumentator.h"

#include <glad/glad.h>


namespace Neat
{
   // ---------------------------------------------------------------------- //
   // BufferElement -------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   BufferElement::BufferElement(ShaderDataType type, const std::string& name,
      Bool normalized)
      : type(type)
      , name(name)
      , size(shaderDataTypeSize(type))
      , componentCount(shaderDataTypeComponentCount(type))
      , dataType(shaderDataTypeToOpenGLBaseType(type))
      , normalized(normalized ? GL_TRUE : GL_FALSE)
   {}

   // ---------------------------------------------------------------------- //
   // VertexBuffer --------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   VertexBuffer::VertexBuffer(UInt size)
   {
      NT_PROFILE_FUNCTION();

      glCreateBuffers(1, &this->id);
      glBindBuffer(GL_ARRAY_BUFFER, this->id);
      glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
   }

   VertexBuffer::VertexBuffer(Float* vertices, UInt size)
   {
      NT_PROFILE_FUNCTION();

      glCreateBuffers(1, &this->id);
      glBindBuffer(GL_ARRAY_BUFFER, this->id);
      glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
   }

   VertexBuffer::~VertexBuffer()
   {

      NT_PROFILE_FUNCTION();
      glDeleteBuffers(1, &this->id);
   }

   void VertexBuffer::bind() const
   {
      NT_PROFILE_FUNCTION();

      glBindBuffer(GL_ARRAY_BUFFER, this->id);
   }

   void VertexBuffer::unbind() const
   {
      NT_PROFILE_FUNCTION();

      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   void VertexBuffer::setData(const void* data, IntLong size)
   {
      this->bind();
      glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
   }

   void VertexBuffer::setLayout(const BufferLayout& layout)
   {
      this->layout = layout;
   }

   // ---------------------------------------------------------------------- //
   // Indexbuffer ---------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   IndexBuffer::IndexBuffer(UInt* indices, Int count)
      : count(count)
   {
      NT_PROFILE_FUNCTION();

      glCreateBuffers(1, &this->id);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
         count * sizeof(count), indices, GL_STATIC_DRAW);
   }

   IndexBuffer::~IndexBuffer()
   {
      NT_PROFILE_FUNCTION();

      glDeleteBuffers(1, &this->id);
   }

   void IndexBuffer::bind() const
   {
      NT_PROFILE_FUNCTION();

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
   }

   void IndexBuffer::unbind() const
   {
      NT_PROFILE_FUNCTION();

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }

}