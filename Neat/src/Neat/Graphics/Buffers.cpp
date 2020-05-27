#include "Neat/Graphics/Buffers.h"

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
      , size(OpenGLTypeConverter::sizeInBytes(type))
      , componentCount(OpenGLTypeConverter::componentCount(type))
      , dataType(OpenGLTypeConverter::baseType(type))
      , normalized(normalized ? GL_TRUE : GL_FALSE)
   {}

   // ---------------------------------------------------------------------- //
   // BufferLayout --------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   BufferLayout::BufferLayout(
      const std::initializer_list<BufferElement>& elements)
      : m_elements(elements)
   {
      UInt index = 0;
      for (auto& element : m_elements)
      {
         element.index = index++;
         element.offset = m_offset;
         m_offset += element.size;
      }
   }

   // ---------------------------------------------------------------------- //
   // VertexBuffer --------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   VertexBuffer::VertexBuffer(UInt size)
   {
      glCreateBuffers(1, &m_id);
      glBindBuffer(GL_ARRAY_BUFFER, m_id);
      glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
   }

   VertexBuffer::VertexBuffer(float* vertices, UInt size)
   {
      glCreateBuffers(1, &m_id);
      glBindBuffer(GL_ARRAY_BUFFER, m_id);
      glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
   }

   VertexBuffer::~VertexBuffer()
   {
      glDeleteBuffers(1, &m_id);
   }

   void VertexBuffer::bind() const
   {
      glBindBuffer(GL_ARRAY_BUFFER, m_id);
   }

   void VertexBuffer::unbind() const
   {
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
      glCreateBuffers(1, &m_id);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
         m_count * sizeof(m_count), indices, GL_STATIC_DRAW);
   }

   IndexBuffer::~IndexBuffer()
   {
      glDeleteBuffers(1, &m_id);
   }

   void IndexBuffer::bind() const
   {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
   }

   void IndexBuffer::unbind() const
   {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }

}