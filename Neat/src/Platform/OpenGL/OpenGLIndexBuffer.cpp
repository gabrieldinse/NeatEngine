#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLIndexBuffer.hpp"

#include <glad/glad.h>

namespace Neat {
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