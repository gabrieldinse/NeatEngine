#include "NeatPCH.hpp"

#include "GraphicsContext.hpp"

#include "Platform/OpenGL/OpenGLGraphicsContext.hpp"
#include "Graphics/RendererAPI.hpp"

namespace Neat {
Scope<GraphicsContext> GraphicsContext::create(void *window) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::OpenGL:
      return makeScope<OpenGLGraphicsContext>(
          static_cast<GLFWwindow *>(window));
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
      return nullptr;
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}
}  // namespace Neat