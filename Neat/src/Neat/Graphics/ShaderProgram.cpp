#include "NeatPCH.hpp"

#include "Neat/Graphics/Renderer.hpp"
#include "Neat/Graphics/ShaderProgram.hpp"
#include "Platform/OpenGL/OpenGLShaderProgram.hpp"

namespace Neat {
std::shared_ptr<ShaderProgram> ShaderProgram::create(
    const std::string &filepath) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLShaderProgram>(filepath);
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}

std::shared_ptr<ShaderProgram> ShaderProgram::create(
    const std::string &name, const std::string &filepath) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLShaderProgram>(name, filepath);
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}

std::shared_ptr<ShaderProgram> ShaderProgram::create(
    const std::string &name, const std::string &vertexSource,
    const std::string &fragmentSource) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return std::make_shared<OpenGLShaderProgram>(name, vertexSource,
                                                   fragmentSource);
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}
}  // namespace Neat