#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLBuffers.hpp"

#include <glad/glad.h>

namespace Neat {

// ---------------------------------------------------------------------- //
// OpenGLVertexBuffer ---------------------------------------------------------
// //
// ---------------------------------------------------------------------- //
OpenGLVertexBuffer::OpenGLVertexBuffer(UInt32 size) {
  glCreateBuffers(1, &m_id);
  bind();
  glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, UInt32 size) {
  glCreateBuffers(1, &m_id);
  bind();
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &m_id); }

void OpenGLVertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

void OpenGLVertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void OpenGLVertexBuffer::setData(const void *data, UInt32 size) {
  bind();
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void OpenGLVertexBuffer::setLayout(const BufferLayout &layout) {
  m_layout = layout;
}

// ---------------------------------------------------------------------- //
// Indexbuffer ---------------------------------------------------------- //
// ---------------------------------------------------------------------- //
OpenGLIndexBuffer::OpenGLIndexBuffer(UInt32 *indices, UInt32 count)
    : m_count(count) {
  glCreateBuffers(1, &m_id);
  bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(m_count), indices,
               GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &m_id); }

void OpenGLIndexBuffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void OpenGLIndexBuffer::unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}  // namespace Neat