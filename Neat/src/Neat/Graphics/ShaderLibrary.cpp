#include "NeatPCH.hpp"

#include "Neat/Graphics/Renderer.hpp"
#include "Neat/Graphics/ShaderLibrary.hpp"
#include "Platform/OpenGL/OpenGLShaderProgram.hpp"

namespace Neat {
void ShaderLibrary::add(const Ref<ShaderProgram> &shader) {
  auto &name = shader->getName();
  NT_CORE_ASSERT(exists(name), "ShaderProgram already exists!");

  m_shaders[name] = shader;
}

void ShaderLibrary::add(const std::string &name,
                        const Ref<ShaderProgram> &shader) {
  NT_CORE_ASSERT(exists(name), "ShaderProgram already exists!");

  shader->setName(name);
  m_shaders[name] = shader;
}

Ref<ShaderProgram> ShaderLibrary::load(const std::string &filepath) {
  auto shader = ShaderProgram::create(filepath);
  add(shader);

  return shader;
}

Ref<ShaderProgram> ShaderLibrary::load(const std::string &name,
                                       const std::string &filepath) {
  auto shader = ShaderProgram::create(name, filepath);
  add(shader);

  return shader;
}

Ref<ShaderProgram> ShaderLibrary::get(const std::string &name) {
  NT_CORE_ASSERT(exists(name), "ShaderProgram not found!");

  return m_shaders[name];
}

bool ShaderLibrary::exists(const std::string &name) const {
  return (m_shaders.find(name) != m_shaders.end());
}
}  // namespace Neat