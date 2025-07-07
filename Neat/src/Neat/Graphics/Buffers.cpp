#include "NeatPCH.hpp"

#include "Neat/Graphics/Buffers.hpp"
#include "Neat/Graphics/RendererAPI.hpp"
#include "Platform/OpenGL/OpenGLBuffers.hpp"

namespace Neat {
// ---------------------------------------------------------------------- //
// BufferElement -------------------------------------------------------- //
// ---------------------------------------------------------------------- //
BufferElement::BufferElement(ShaderDataType type, const std::string &name,
                             bool normalized)
    : type(type),
      name(name),
      size(getShaderDataTypeSize(type)),
      componentCount(getShaderDataTypeComponentCount(type)),
      normalized(normalized) {}

// ---------------------------------------------------------------------- //
// BufferLayout --------------------------------------------------------- //
// ---------------------------------------------------------------------- //
BufferLayout::BufferLayout(const std::initializer_list<BufferElement> &elements)
    : m_elements(elements) {
  UInt32 index = 0;
  for (auto &element : m_elements) {
    element.index = index++;
    element.offset = m_offset;
    m_offset += element.size;
  }
}

std::shared_ptr<VertexBuffer> VertexBuffer::create(UInt32 size) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLVertexBuffer>(size);
  }

  NT_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

std::shared_ptr<VertexBuffer> VertexBuffer::create(float *vertices,
                                                   UInt32 size) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLVertexBuffer>(vertices, size);
  }

  NT_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

std::shared_ptr<IndexBuffer> IndexBuffer::create(UInt32 *indices,
                                                 UInt32 count) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLIndexBuffer>(indices, count);
  }

  NT_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
}  // namespace Neat