#include "NeatPCH.hpp"

#include "FrameBuffer.hpp"

#include "Platform/OpenGL/OpenGLFrameBuffer.hpp"
#include "Neat/Graphics/Renderer.hpp"

namespace Neat {
Ref<FrameBuffer> FrameBuffer::create(const FrameBufferSpecification &spec) {
  NT_PROFILE_FUNCTION();
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::OpenGL:
      return makeRef<OpenGLFrameBuffer>(spec);
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
      return nullptr;
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}
}  // namespace Neat