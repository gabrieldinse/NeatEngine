#include "Neat/Graphics/VertexArray.hpp"
#include "Neat/Core/Log.hpp"
#include "Neat/Graphics/Renderer.hpp"

#include <glad/glad.h>

namespace Neat {
VertexArray::VertexArray() { glCreateVertexArrays(1, &m_id); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_id); }

void VertexArray::bind() const { glBindVertexArray(m_id); }

void VertexArray::unbind() const { glBindVertexArray(0); }

void VertexArray::addVertexBuffer(
    const std::shared_ptr<VertexBuffer> &vertexBuffer) {
  NT_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(),
                 "VertexBuffer has no layout.");

  bind();
  vertexBuffer->bind();

  const auto &layout = vertexBuffer->getLayout();
  for (const auto &element : layout) {
    glVertexAttribPointer(
        element.index, element.componentCount, element.dataType,
        element.normalized, layout.getOffset(),
        static_cast<void *>(static_cast<char *>(0) + element.offset));
    glEnableVertexAttribArray(element.index);
  }

  m_vertexBuffers.push_back(vertexBuffer);
}

void VertexArray::setIndexBuffer(
    const std::shared_ptr<IndexBuffer> &indexBuffer) {
  bind();
  indexBuffer->bind();
  m_indexBuffer = indexBuffer;
}
} // namespace Neat