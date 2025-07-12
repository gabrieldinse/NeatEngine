#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLShaderDataType.hpp"
#include "Platform/OpenGL/OpenGLShaderProgram.hpp"

#include <glad/glad.h>

namespace Neat {
OpenGLShaderProgram::OpenGLShaderProgram(const std::string &filepath)
    : m_id(glCreateProgram()),
      m_name(std::filesystem::path(filepath).stem().string()) {
  OpenGLShaderProgramBuilder(m_id, filepath).build();
}

OpenGLShaderProgram::OpenGLShaderProgram(const std::string &name,
                                         const std::string &filepath)
    : m_id(glCreateProgram()), m_name(name) {
  OpenGLShaderProgramBuilder(m_id, filepath).build();
}

OpenGLShaderProgram::OpenGLShaderProgram(const std::string &name,
                                         const std::string &vertexSource,
                                         const std::string &fragmentSource)
    : m_id(glCreateProgram()), m_name(name) {
  OpenGLShaderProgramBuilder(m_id, vertexSource, fragmentSource).build();
}

OpenGLShaderProgram::~OpenGLShaderProgram() { glDeleteProgram(m_id); }

void OpenGLShaderProgram::use() const { glUseProgram(m_id); }

void OpenGLShaderProgram::unuse() const { glUseProgram(0); }

void OpenGLShaderProgram::set(const std::string &name, float value) {
  glUniform1f(getUniformLocation(name), value);
}

void OpenGLShaderProgram::set(const std::string &name, Vector2F values) {
  glUniform2f(getUniformLocation(name), values.x, values.y);
}

void OpenGLShaderProgram::set(const std::string &name, Vector3F values) {
  glUniform3f(getUniformLocation(name), values.x, values.y, values.z);
}

void OpenGLShaderProgram::set(const std::string &name, Vector4F values) {
  glUniform4f(getUniformLocation(name), values.x, values.y, values.z, values.w);
}

void OpenGLShaderProgram::set(const std::string &name, Int32 value) {
  glUniform1i(getUniformLocation(name), value);
}

void OpenGLShaderProgram::set(const std::string &name, Int32 *values,
                              UInt32 count) {
  glUniform1iv(getUniformLocation(name), count, values);
}

void OpenGLShaderProgram::set(const std::string &name, Matrix3F matrix) {
  glUniformMatrix3fv(getUniformLocation(name), 1, GL_TRUE,
                     matrix.dataPointer());
}

void OpenGLShaderProgram::set(const std::string &name, Matrix4F matrix) {
  glUniformMatrix4fv(getUniformLocation(name), 1, GL_TRUE,
                     matrix.dataPointer());
}

Int32 OpenGLShaderProgram::getUniformLocation(const std::string &name) {
  if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
    return m_uniformLocationCache[name];
  }

  auto location = glGetUniformLocation(m_id, name.c_str());
  NT_CORE_ASSERT(location != -1, "Uniform does not exist.");

  m_uniformLocationCache[name] = location;
  return location;
}
}  // namespace Neat