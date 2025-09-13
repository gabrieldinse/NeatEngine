#include "NeatPCH.hpp"

#include "RendererAPI.hpp"

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Neat {
RendererAPI::API RendererAPI::s_api = RendererAPI::API::OpenGL;

Scope<RendererAPI> RendererAPI::create() {
  switch (s_api) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return makeScope<OpenGLRendererAPI>();
  }
  NT_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
}  // namespace Neat