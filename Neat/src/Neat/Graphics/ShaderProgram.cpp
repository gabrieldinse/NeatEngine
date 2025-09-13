#include "NeatPCH.hpp"

#include "Renderer.hpp"
#include "ShaderProgram.hpp"

#include "Platform/OpenGL/OpenGLShaderProgram.hpp"

namespace Neat {
Ref<ShaderProgram> ShaderProgram::create(const std::string &filepath) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return makeRef<OpenGLShaderProgram>(filepath);
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}

Ref<ShaderProgram> ShaderProgram::create(const std::string &name,
                                         const std::string &filepath) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return makeRef<OpenGLShaderProgram>(name, filepath);
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}

Ref<ShaderProgram> ShaderProgram::create(const std::string &name,
                                         const std::string &vertexSource,
                                         const std::string &fragmentSource) {
  switch (RendererAPI::getAPI()) {
    case RendererAPI::API::None:
      NT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return makeRef<OpenGLShaderProgram>(name, vertexSource, fragmentSource);
    default:
      NT_CORE_ASSERT(false, "Unknown RendererAPI!");
      return nullptr;
  }
}
}  // namespace Neat