#include "NeatPCH.hpp"

#include "Neat/Graphics/IndexBuffer.hpp"
#include "Neat/Graphics/RendererAPI.hpp"
#include "Platform/OpenGL/OpenGLIndexBuffer.hpp"

namespace Neat {
Ref<IndexBuffer> IndexBuffer::create(UInt32 *indices, UInt32 count) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return makeRef<OpenGLIndexBuffer>(indices, count);
  }

  NT_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
}  // namespace Neat