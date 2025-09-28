#include "NeatPCH.hpp"

#include "OpenGLUniformBuffer.hpp"

#include <glad/glad.h>

namespace Neat {
OpenGLUniformBuffer::OpenGLUniformBuffer(UInt32 size, UInt32 binding)
    : m_size(size) {
  NT_PROFILE_FUNCTION();

  glCreateBuffers(1, &m_id);
  glNamedBufferData(m_id, size, nullptr, GL_DYNAMIC_DRAW);
  glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_id);
}

OpenGLUniformBuffer::~OpenGLUniformBuffer() {
  NT_PROFILE_FUNCTION();

  glDeleteBuffers(1, &m_id);
}

void OpenGLUniformBuffer::setData(const Matrix4F &matrix, UInt32 offset) {
  NT_PROFILE_FUNCTION();

  NT_CORE_ASSERT(offset + sizeof(matrix) <= m_size,
                 "Data exceeds buffer size!");
  Matrix4F transposed{transpose(matrix)};
  glNamedBufferSubData(m_id, offset, sizeof(transposed), transposed.data());
}

void OpenGLUniformBuffer::setData(const void *data, UInt32 size,
                                  UInt32 offset) {
  NT_PROFILE_FUNCTION();

  NT_CORE_ASSERT(offset + size <= m_size, "Data exceeds buffer size!");

  glNamedBufferSubData(m_id, offset, size, data);
}
}  // namespace Neat