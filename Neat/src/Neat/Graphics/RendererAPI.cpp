#include "NeatPCH.hpp"

#include "Neat/Graphics/RendererAPI.hpp"
#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Neat {
RendererAPI::API RendererAPI::s_api = RendererAPI::API::OpenGL;

std::unique_ptr<RendererAPI> RendererAPI::create() {
  switch (s_api) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return std::make_unique<OpenGLRendererAPI>();
  }
  NT_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
}  // namespace Neat