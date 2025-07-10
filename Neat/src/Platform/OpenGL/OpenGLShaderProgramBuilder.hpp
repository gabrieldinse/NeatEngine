#pragma once

#include <string>
#include <unordered_map>

#include "Neat/Core/Types.hpp"

namespace Neat {
class OpenGLShaderProgramBuilder {
 public:
  OpenGLShaderProgramBuilder(UInt32 programId, const std::string &filepath);
  OpenGLShaderProgramBuilder(UInt32 programId, const std::string &vertexSource,
                             const std::string &fragmentSource);
  void build();

 private:
  void preprocessShaderSource();

 private:
  UInt32 m_id = 0;
  std::string m_fileContent;
  std::unordered_map<UInt32, std::string> m_shaderSources;
};
}  // namespace Neat