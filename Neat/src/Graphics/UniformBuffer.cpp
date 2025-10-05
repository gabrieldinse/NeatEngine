#include "NeatPCH.hpp"

#include "UniformBuffer.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLUniformBuffer.hpp"

namespace Neat {
Scope<UniformBuffer> UniformBuffer::create(UInt32 size, UInt32 binding) {
  NT_PROFILE_FUNCTION();

  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::OpenGL:
      return makeScope<OpenGLUniformBuffer>(size, binding);
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
      return nullptr;
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}
}  // namespace Neat