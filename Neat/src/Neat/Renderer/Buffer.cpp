#include "Neat/Renderer/Buffer.h"
#include "Neat/Debug/Instrumentator.h"

#include <glad/glad.h>


namespace Neat
{
   // ---------------------------------------------------------------------- //
   // BufferElement -------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   BufferElement::BufferElement(ShaderDataType type, const std::string& name,
      bool normalized)
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

      glCreateBuffers(1, &m_id);
      glBindBuffer(GL_ARRAY_BUFFER, m_id);
      glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
   }

   VertexBuffer::VertexBuffer(float* vertices, UInt size)
   {
      NT_PROFILE_FUNCTION();

      glCreateBuffers(1, &m_id);
      glBindBuffer(GL_ARRAY_BUFFER, m_id);
      glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
   }

   VertexBuffer::~VertexBuffer()
   {

      NT_PROFILE_FUNCTION();
      glDeleteBuffers(1, &m_id);
   }

   void VertexBuffer::bind() const
   {
      NT_PROFILE_FUNCTION();

      glBindBuffer(GL_ARRAY_BUFFER, m_id);
   }

   void VertexBuffer::unbind() const
   {
      NT_PROFILE_FUNCTION();

      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   void VertexBuffer::setData(const void* m_data, IntLong size)
   {
      bind();
      glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_data);
   }

   void VertexBuffer::setLayout(const BufferLayout& layout)
   {
      m_layout = layout;
   }

   // ---------------------------------------------------------------------- //
   // Indexbuffer ---------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   IndexBuffer::IndexBuffer(UInt* indices, Int count)
      : m_count(count)
   {
      NT_PROFILE_FUNCTION();

      glCreateBuffers(1, &m_id);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
         m_count * sizeof(m_count), indices, GL_STATIC_DRAW);
   }

   IndexBuffer::~IndexBuffer()
   {
      NT_PROFILE_FUNCTION();

      glDeleteBuffers(1, &m_id);
   }

   void IndexBuffer::bind() const
   {
      NT_PROFILE_FUNCTION();

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
   }

   void IndexBuffer::unbind() const
   {
      NT_PROFILE_FUNCTION();

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }

}