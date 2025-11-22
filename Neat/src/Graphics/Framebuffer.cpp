#include "NeatPCH.hpp"

#include "Framebuffer.hpp"

#include "Platform/OpenGL/OpenGLFramebuffer.hpp"
#include "Graphics/RendererAPI.hpp"

namespace Neat {
Ref<Framebuffer> Framebuffer::create(const FramebufferSpecification &spec) {
  NT_PROFILE_FUNCTION();
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::OpenGL:
      return makeRef<OpenGLFramebuffer>(spec);
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
      return nullptr;
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}
}  // namespace Neat