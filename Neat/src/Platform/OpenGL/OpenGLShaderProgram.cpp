#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLUtils.hpp"
#include "Platform/OpenGL/OpenGLShaderProgram.hpp"
#include "Neat/Utils/ReadFile.hpp"

#include <glad/glad.h>

namespace Neat {
OpenGLShaderProgram::OpenGLShaderProgram(const std::string &filepath)
    : m_id(glCreateProgram()),
      m_name(std::filesystem::path(filepath).stem().string()) {
  NT_PROFILE_FUNCTION();
  build(filepath);
}

OpenGLShaderProgram::OpenGLShaderProgram(const std::string &name,
                                         const std::string &filepath)
    : m_id(glCreateProgram()), m_name(name) {
  NT_PROFILE_FUNCTION();
  build(filepath);
}

OpenGLShaderProgram::OpenGLShaderProgram(const std::string &name,
                                         const std::string &vertexSource,
                                         const std::string &fragmentSource)
    : m_id(glCreateProgram()), m_name(name) {
  NT_PROFILE_FUNCTION();
  std::unordered_map<UInt32, std::string> shader_sources = {
      {GL_VERTEX_SHADER, vertexSource},
      {GL_FRAGMENT_SHADER, fragmentSource},
  };
  build(shader_sources);
}

OpenGLShaderProgram::~OpenGLShaderProgram() {
  NT_PROFILE_FUNCTION();
  glDeleteProgram(m_id);
}

void OpenGLShaderProgram::bind() const {
  NT_PROFILE_FUNCTION();
  glUseProgram(m_id);
}

void OpenGLShaderProgram::unbind() const {
  NT_PROFILE_FUNCTION();
  glUseProgram(0);
}

void OpenGLShaderProgram::set(const std::string &name, float value) {
  NT_PROFILE_FUNCTION();
  glUniform1f(getUniformLocation(name), value);
}

void OpenGLShaderProgram::set(const std::string &name, Vector2F values) {
  NT_PROFILE_FUNCTION();
  glUniform2f(getUniformLocation(name), values.x(), values.y());
}

void OpenGLShaderProgram::set(const std::string &name, Vector3F values) {
  NT_PROFILE_FUNCTION();
  glUniform3f(getUniformLocation(name), values.x(), values.y(), values.z());
}

void OpenGLShaderProgram::set(const std::string &name, Vector4F values) {
  NT_PROFILE_FUNCTION();
  glUniform4f(getUniformLocation(name), values.x(), values.y(), values.z(),
              values.w());
}

void OpenGLShaderProgram::set(const std::string &name, Int32 value) {
  NT_PROFILE_FUNCTION();
  glUniform1i(getUniformLocation(name), value);
}

void OpenGLShaderProgram::set(const std::string &name, Int32 *values,
                              UInt32 count) {
  NT_PROFILE_FUNCTION();
  glUniform1iv(getUniformLocation(name), count, values);
}

void OpenGLShaderProgram::set(const std::string &name, Matrix3F matrix) {
  NT_PROFILE_FUNCTION();
  glUniformMatrix3fv(getUniformLocation(name), 1, GL_TRUE, matrix.data());
}

void OpenGLShaderProgram::set(const std::string &name, Matrix4F matrix) {
  NT_PROFILE_FUNCTION();
  glUniformMatrix4fv(getUniformLocation(name), 1, GL_TRUE, matrix.data());
}

Int32 OpenGLShaderProgram::getUniformLocation(const std::string &name) {
  NT_PROFILE_FUNCTION();
  if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
    return m_uniformLocationCache[name];
  }

  auto location = glGetUniformLocation(m_id, name.c_str());
  NT_CORE_ASSERT(location != -1, "Uniform does not exist.");

  m_uniformLocationCache[name] = location;
  return location;
}

void OpenGLShaderProgram::build(const std::string &filepath) {
  NT_PROFILE_FUNCTION();
  auto result = readFile(filepath);
  if (not result) {
    NT_CORE_ERROR("Failed to read shader file: {0}.", result.error().message);
    NT_CORE_ASSERT(false, "");
    return;
  }

  const auto &shader_sources_pack = *result;
  NT_CORE_TRACE("Shader sources:\n{0}", shader_sources_pack);
  auto shader_sources = splitShaderSources(shader_sources_pack);
  build(shader_sources);
}

void OpenGLShaderProgram::build(
    std::unordered_map<UInt32, std::string> &shader_sources) {
  NT_PROFILE_FUNCTION();
  std::vector<UInt32> shader_ids;
  for (const auto &[type, source] : shader_sources) {
    UInt32 shader_id = compileShader(type, source);
    shader_ids.push_back(shader_id);
  }
  linkProgram(shader_ids);
}

std::unordered_map<UInt32, std::string> OpenGLShaderProgram::splitShaderSources(
    const std::string &shaderSourcesPack) {
  NT_PROFILE_FUNCTION();
  constexpr const char *type_token = "// #Type:";
  auto type_token_length = strlen(type_token);
  auto pos = shaderSourcesPack.find(type_token, 0);
  std::unordered_map<UInt32, std::string> shader_sources;

  while (pos != std::string::npos) {
    auto shader_type_begin =
        shaderSourcesPack.find_first_not_of(" \t", pos + type_token_length);
    auto shader_type_end =
        shaderSourcesPack.find_first_of(" \t\r\n", shader_type_begin);
    auto eol_pos = shaderSourcesPack.find_first_of("\r\n", shader_type_end);

    NT_CORE_ASSERT(eol_pos != std::string::npos,
                   "OpenGLShaderProgram source syntax error.");

    auto shader_type_name = shaderSourcesPack.substr(
        shader_type_begin, shader_type_end - shader_type_begin);
    auto shader_type = OpenGL::getShaderDataType(shader_type_name);

    auto next_line_pos = shaderSourcesPack.find_first_not_of("\r\n", eol_pos);
    pos = shaderSourcesPack.find(type_token, next_line_pos);
    std::string shader_source = shaderSourcesPack.substr(
        next_line_pos, (pos == std::string::npos ? pos : pos - next_line_pos));

    switch (shader_type) {
      case GL_VERTEX_SHADER:
        shader_sources[GL_VERTEX_SHADER] = shader_source;
        break;
      case GL_FRAGMENT_SHADER:
        shader_sources[GL_FRAGMENT_SHADER] = shader_source;
        break;
      default:
        NT_CORE_ASSERT(false, "Unknown shader type.");
    }
  }

  return shader_sources;
}

UInt32 OpenGLShaderProgram::compileShader(UInt32 type,
                                          const std::string &shaderSource) {
  NT_PROFILE_FUNCTION();
  UInt32 shader_id = glCreateShader(type);

  const char *c_str_source = shaderSource.c_str();
  glShaderSource(shader_id, 1, &c_str_source, 0);
  glCompileShader(shader_id);

  Int32 compiled = 0;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
  if (compiled == GL_FALSE) {
    Int32 max_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<char> info_log(max_length);
    glGetShaderInfoLog(shader_id, max_length, &max_length, &info_log[0]);

    glDeleteShader(shader_id);

    NT_CORE_ERROR("OpenGLShaderProgram compilation failure:\n{0}",
                  info_log.data());
    NT_CORE_ASSERT(false, "");
  }

  glAttachShader(m_id, shader_id);
  return shader_id;
}

void OpenGLShaderProgram::linkProgram(std::vector<UInt32> shaderIDs) {
  NT_PROFILE_FUNCTION();
  glLinkProgram(m_id);

  Int32 linked = 0;
  glGetProgramiv(m_id, GL_LINK_STATUS, static_cast<Int32 *>(&linked));
  if (linked == GL_FALSE) {
    Int32 max_length = 0;
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &max_length);

    std::vector<char> info_log(max_length);
    glGetProgramInfoLog(m_id, max_length, &max_length, &info_log[0]);

    glDeleteProgram(m_id);
    for (UInt32 shaderId : shaderIDs) {
      glDetachShader(m_id, shaderId);
    }

    NT_CORE_ERROR("OpenGLShaderProgram link failure:\n{0}.", info_log.data());
    NT_CORE_ASSERT(false, "");
  }

  for (UInt32 shaderId : shaderIDs) {
    glDeleteShader(shaderId);
  }
  NT_CORE_TRACE("OpenGLShaderProgram linked successfully.");
}
}  // namespace Neat