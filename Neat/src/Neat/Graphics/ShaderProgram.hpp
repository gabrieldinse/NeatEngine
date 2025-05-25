#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/Uniform.hpp"
#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
// ---------------------------------------------------------------------- //
// ShaderProgramBuilder ------------------------------------------------- //
// ---------------------------------------------------------------------- //
class ShaderProgramBuilder {
public:
  ShaderProgramBuilder(UInt32 programId, const std::string &filepath);
  ShaderProgramBuilder(UInt32 programId, const std::string &vertexSource,
                       const std::string &fragmentSource);
  void build();

private:
  void preprocessShaderSource();

private:
  UInt32 m_id = 0;
  std::string m_fileContent;
  std::unordered_map<UInt32, std::string> m_shaderSources;
};

// ---------------------------------------------------------------------- //
// ShaderProgram -------------------------------------------------------- //
// ---------------------------------------------------------------------- //
class ShaderProgram {
public:
  ShaderProgram(const std::string &filepath);
  ShaderProgram(const std::string &name, const std::string &filepath);
  ShaderProgram(const std::string &name, const std::string &vertexSource,
                const std::string &fragmentSource);
  virtual ~ShaderProgram();

  void use() const;
  void unuse() const;

  const std::string &getName() const { return m_name; }
  void setName(const std::string &name) { m_name = name; }

  UInt32 getId() const { return m_id; }

  template <ShaderDataType UniformType>
  Uniform<UniformType> getUniform(const std::string &name) {
    return Uniform<UniformType>(name, *m_uniformLibrary);
  }

private:
  UInt32 m_id = 0;
  std::unique_ptr<UniformLibrary> m_uniformLibrary;
  std::string m_name;
};

// ---------------------------------------------------------------------- //
// ShaderLibrary -------------------------------------------------------- //
// ---------------------------------------------------------------------- //
class ShaderLibrary {
public:
  void add(const std::shared_ptr<ShaderProgram> &shader);
  void add(const std::string &name,
           const std::shared_ptr<ShaderProgram> &shader);
  std::shared_ptr<ShaderProgram> load(const std::string &filepath);
  std::shared_ptr<ShaderProgram> load(const std::string &name,
                                      const std::string &filepath);
  std::shared_ptr<ShaderProgram> get(const std::string &name);

  bool exists(const std::string &name) const;

private:
  std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> m_shaders;
};
} // namespace Neat