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

void ShaderLibrary::add(const std::shared_ptr<ShaderProgram> &shader) {
  auto &name = shader->getName();
  NT_CORE_ASSERT(exists(name), "ShaderProgram already exists!");

  m_shaders[name] = shader;
}

void ShaderLibrary::add(const std::string &name,
                        const std::shared_ptr<ShaderProgram> &shader) {
  NT_CORE_ASSERT(exists(name), "ShaderProgram already exists!");

  shader->setName(name);
  m_shaders[name] = shader;
}

std::shared_ptr<ShaderProgram> ShaderLibrary::load(
    const std::string &filepath) {
  auto shader = ShaderProgram::create(filepath);
  add(shader);

  return shader;
}

std::shared_ptr<ShaderProgram> ShaderLibrary::load(
    const std::string &name, const std::string &filepath) {
  auto shader = ShaderProgram::create(name, filepath);
  add(shader);

  return shader;
}

std::shared_ptr<ShaderProgram> ShaderLibrary::get(const std::string &name) {
  NT_CORE_ASSERT(exists(name), "ShaderProgram not found!");

  return m_shaders[name];
}

bool ShaderLibrary::exists(const std::string &name) const {
  return (m_shaders.find(name) != m_shaders.end());
}
}  // namespace Neat