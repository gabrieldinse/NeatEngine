#include "NeatPCH.hpp"

#include "VertexBuffer.hpp"
#include "RendererAPI.hpp"

#include "Core/Assert.hpp"
#include "Platform/OpenGL/OpenGLVertexBuffer.hpp"

namespace Neat {

Ref<VertexBuffer> VertexBuffer::create(UInt32 size) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return makeRef<OpenGLVertexBuffer>(size);
  }

  NT_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

Ref<VertexBuffer> VertexBuffer::create(float *vertices, UInt32 size) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return makeRef<OpenGLVertexBuffer>(vertices, size);
  }

  NT_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
}  // namespace Neat