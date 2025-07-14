#include "NeatPCH.hpp"

#include "Neat/Graphics/VertexArray.hpp"
#include "Neat/Graphics/Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Neat {
Ref<VertexArray> VertexArray::create() {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return makeRef<OpenGLVertexArray>();
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}
}  // namespace Neat