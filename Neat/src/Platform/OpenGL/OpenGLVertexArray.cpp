#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLVertexArray.hpp"
#include "Platform/OpenGL/OpenGLUtils.hpp"
#include "Neat/Graphics/Renderer.hpp"

#include <glad/glad.h>

namespace Neat {
OpenGLVertexArray::OpenGLVertexArray() {
  NT_PROFILE_FUNCTION();
  glCreateVertexArrays(1, &m_id);
}

OpenGLVertexArray::~OpenGLVertexArray() {
  NT_PROFILE_FUNCTION();
  glDeleteVertexArrays(1, &m_id);
}

void OpenGLVertexArray::bind() const {
  NT_PROFILE_FUNCTION();
  glBindVertexArray(m_id);
}

void OpenGLVertexArray::unbind() const { glBindVertexArray(0); }

void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {
  NT_PROFILE_FUNCTION();
  NT_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(),
                 "VertexBuffer has no layout.");

  bind();
  vertexBuffer->bind();

  const auto &layout = vertexBuffer->getLayout();
  for (const auto &element : layout) {
    glVertexAttribPointer(
        element.index, element.componentCount,
        OpenGL::getPrimitiveType(element.type),
        static_cast<GLboolean>(element.normalized), layout.getOffset(),
        static_cast<void *>(static_cast<char *>(0) + element.offset));
    glEnableVertexAttribArray(element.index);
  }

  m_vertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) {
  NT_PROFILE_FUNCTION();
  bind();
  indexBuffer->bind();
  m_indexBuffer = indexBuffer;
}
}  // namespace Neat