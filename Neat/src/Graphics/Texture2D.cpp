#include "NeatPCH.hpp"

#include "Texture2D.hpp"
#include "Renderer.hpp"

#include "Platform/OpenGL/OpenGLTexture2D.hpp"

namespace Neat {
Ref<Texture2D> Texture2D::create(Int32 width, Int32 height) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return makeRef<OpenGLTexture2D>(width, height);
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}

Ref<Texture2D> Texture2D::create(const std::string &filepath) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return makeRef<OpenGLTexture2D>(filepath);
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}
}  // namespace Neat
