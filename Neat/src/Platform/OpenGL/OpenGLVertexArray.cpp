#include "NeatPCH.hpp"

#include "OpenGLVertexArray.hpp"
#include "OpenGLUtils.hpp"

#include "Graphics/Renderer.hpp"

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
  setLayouts(vertexBuffer);
  m_vertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setLayouts(const Ref<VertexBuffer> &vertexBuffer) {
  const auto &layout = vertexBuffer->getLayout();
  for (const auto &element : layout) {
    switch (element.type) {
      case ShaderDataType::Float:
      case ShaderDataType::Vector2F:
      case ShaderDataType::Vector3F:
      case ShaderDataType::Vector4F:
        glVertexAttribPointer(
            element.index, element.componentCount,
            OpenGL::getPrimitiveType(element.type),
            static_cast<GLboolean>(element.normalized), layout.getOffset(),
            static_cast<void *>(static_cast<char *>(0) + element.offset));
        glEnableVertexAttribArray(element.index);
        break;

      case ShaderDataType::Int:
      case ShaderDataType::Vector2I:
      case ShaderDataType::Vector3I:
      case ShaderDataType::Vector4I:
      case ShaderDataType::UInt:
      case ShaderDataType::Vector2UI:
      case ShaderDataType::Vector3UI:
      case ShaderDataType::Vector4UI:
      case ShaderDataType::Bool:
        glVertexAttribIPointer(
            element.index, element.componentCount,
            OpenGL::getPrimitiveType(element.type), layout.getOffset(),
            static_cast<void *>(static_cast<char *>(0) + element.offset));
        glEnableVertexAttribArray(element.index);
        break;

      case ShaderDataType::Matrix3F:
      case ShaderDataType::Matrix4F:
        for (UInt32 i = 0; i < element.componentCount; ++i) {
          glEnableVertexAttribArray(element.index + i);
          glVertexAttribPointer(
              element.index + i, element.componentCount,
              OpenGL::getPrimitiveType(element.type),
              static_cast<GLboolean>(element.normalized), layout.getOffset(),
              reinterpret_cast<void *>(static_cast<char *>(0) + element.offset +
                                       sizeof(float) * element.componentCount *
                                           i));
          glVertexAttribDivisor(element.index + i, 1);
        }
        break;

      default:
        NT_CORE_ASSERT(false, "Unknown ShaderDataType!");
        break;
    }
  }
}

void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) {
  NT_PROFILE_FUNCTION();
  bind();
  indexBuffer->bind();
  m_indexBuffer = indexBuffer;
}
}  // namespace Neat