#include "NeatPCH.hpp"

#include "Neat/Graphics/Texture.hpp"
#include "Neat/Graphics/Renderer.hpp"
#include "Platform/OpenGL/OpenGLTexture.hpp"

namespace Neat {
std::shared_ptr<Texture2D> Texture2D::create(Int32 width, Int32 height) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLTexture2D>(width, height);
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}

std::shared_ptr<Texture2D> Texture2D::create(const std::string &filepath) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLTexture2D>(filepath);
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}
}  // namespace Neat
