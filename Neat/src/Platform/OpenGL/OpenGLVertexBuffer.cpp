#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"

#include <glad/glad.h>

namespace Neat {
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

void OpenGLVertexBuffer::setLayout(const VertexBufferLayout &layout) {
  m_layout = layout;
}
}  // namespace Neat