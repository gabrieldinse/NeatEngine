#include "Neat/Graphics/Uniform.hpp"
#include "Neat/Core/Log.hpp"
#include "Neat/Graphics/ShaderProgram.hpp"

#include <glad/glad.h>

namespace Neat {
// ---------------------------------------------------------------------- //
// UniformData ---------------------------------------------------------- //
// ---------------------------------------------------------------------- //
struct UniformData {
  UniformData(const std::string &name, Int32 type, Int32 size, Int32 location)
      : name(name), type(type), size(size), location(location) {}

  UniformData() = default;

  std::string name;
  Int32 type;
  Int32 size;
  Int32 location;
};

// ---------------------------------------------------------------------- //
// UniformLibrary-------------------------------------------------------- //
// ---------------------------------------------------------------------- //
UniformLibrary::UniformLibrary(ShaderProgram &shader) : m_shader(shader) {
  GLint uniform_count;
  GLint uniform_name_length;

  glGetProgramiv(m_shader.getId(), GL_ACTIVE_UNIFORMS, &uniform_count);
  glGetProgramiv(m_shader.getId(), GL_ACTIVE_UNIFORM_MAX_LENGTH,
                 &uniform_name_length);
  std::vector<char> name_data(uniform_name_length);

  for (GLint i = 0; i < uniform_count; i++) {
    GLenum type;
    GLint size;

    glGetActiveUniform(m_shader.getId(), i, uniform_name_length, NULL, &size,
                       &type, &name_data[0]);
    std::string name(&name_data[0]);
    auto location = glGetUniformLocation(m_shader.getId(), name.c_str());

    NT_CORE_ASSERT(location != -1, "Uniform does not exist.");

    m_uniforms[std::string(name)] =
        std::make_unique<UniformData>(name, type, size, location);
  }
}

UniformLibrary::~UniformLibrary() {}

bool UniformLibrary::exists(const std::string &name) const {
  return (m_uniforms.find(name) != m_uniforms.end());
}

UniformData &UniformLibrary::operator[](const std::string &name) {
  return *m_uniforms.at(name);
}

const UniformData &UniformLibrary::operator[](const std::string &name) const {
  return *m_uniforms.at(name);
}

// ---------------------------------------------------------------------- //
// UniformBase ---------------------------------------------------------- //
// ---------------------------------------------------------------------- //
UniformBase::~UniformBase() {}

const std::string &UniformBase::getName() const { return m_data->name; }

Int32 UniformBase::getType() const { return m_data->type; }

Int32 UniformBase::getSize() const { return m_data->size; }

Int32 UniformBase::getLocation() const { return m_data->location; }

void UniformBase::checkUniform(ShaderDataType uniformType,
                               const std::string &name,
                               const UniformLibrary &uniformLibrary) {
  NT_CORE_ASSERT(uniformLibrary.exists(name),
                 "Uniform \"" + name + "\" was not found.");

  auto uniform_data = uniformLibrary[name];

  if (uniformType != OpenGLTypeConverter::toShaderDataType(uniform_data.type,
                                                           uniform_data.size))
    NT_CORE_ASSERT(false, "Wrong Uniform type.");
}

// ---------------------------------------------------------------------- //
// Uniform -------------------------------------------------------------- //
// ---------------------------------------------------------------------- //
Uniform<ShaderDataType::Float>::Uniform(const std::string &name,
                                        const UniformLibrary &uniformLibrary) {
  checkUniform(ShaderDataType::Float, name, uniformLibrary);
  m_data = std::make_unique<UniformData>(uniformLibrary[name]);
}

Uniform<ShaderDataType::Vector2F>::Uniform(
    const std::string &name, const UniformLibrary &uniformLibrary) {
  checkUniform(ShaderDataType::Vector2F, name, uniformLibrary);
  m_data = std::make_unique<UniformData>(uniformLibrary[name]);
}

Uniform<ShaderDataType::Vector3F>::Uniform(
    const std::string &name, const UniformLibrary &uniformLibrary) {
  checkUniform(ShaderDataType::Vector3F, name, uniformLibrary);
  m_data = std::make_unique<UniformData>(uniformLibrary[name]);
}

Uniform<ShaderDataType::Vector4F>::Uniform(
    const std::string &name, const UniformLibrary &uniformLibrary) {
  checkUniform(ShaderDataType::Vector4F, name, uniformLibrary);
  m_data = std::make_unique<UniformData>(uniformLibrary[name]);
}

Uniform<ShaderDataType::Int>::Uniform(const std::string &name,
                                      const UniformLibrary &uniformLibrary) {
  checkUniform(ShaderDataType::Int, name, uniformLibrary);
  m_data = std::make_unique<UniformData>(uniformLibrary[name]);
}

Uniform<ShaderDataType::IntArray>::Uniform(
    const std::string &name, const UniformLibrary &uniformLibrary) {
  checkUniform(ShaderDataType::IntArray, name, uniformLibrary);
  m_data = std::make_unique<UniformData>(uniformLibrary[name]);
}

Uniform<ShaderDataType::Matrix3F>::Uniform(
    const std::string &name, const UniformLibrary &uniformLibrary) {
  checkUniform(ShaderDataType::Matrix3F, name, uniformLibrary);
  m_data = std::make_unique<UniformData>(uniformLibrary[name]);
}

Uniform<ShaderDataType::Matrix4F>::Uniform(
    const std::string &name, const UniformLibrary &uniformLibrary) {
  checkUniform(ShaderDataType::Matrix4F, name, uniformLibrary);
  m_data = std::make_unique<UniformData>(uniformLibrary[name]);
}

void Uniform<ShaderDataType::Float>::set(float value) {
  glUniform1f(m_data->location, value);
}

void Uniform<ShaderDataType::Vector2F>::set(Vector2F values) {
  glUniform2f(m_data->location, values.x, values.y);
}

void Uniform<ShaderDataType::Vector3F>::set(Vector3F values) {
  glUniform3f(m_data->location, values.x, values.y, values.z);
}

void Uniform<ShaderDataType::Vector4F>::set(Vector4F values) {
  glUniform4f(m_data->location, values.x, values.y, values.z, values.w);
}

void Uniform<ShaderDataType::Int>::set(Int32 value) {
  glUniform1i(m_data->location, value);
}

void Uniform<ShaderDataType::IntArray>::set(Int32 *values, UInt32 count) {
  glUniform1iv(m_data->location, count, values);
}

void Uniform<ShaderDataType::Matrix3F>::set(Matrix3F matrix) {
  glUniformMatrix3fv(m_data->location, 1, GL_TRUE, matrix.dataPointer());
}

void Uniform<ShaderDataType::Matrix4F>::set(Matrix4F matrix) {
  glUniformMatrix4fv(m_data->location, 1, GL_TRUE, matrix.dataPointer());
}
} // namespace Neat