#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Neat/Core/Types.hpp"
#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {

// ---------------------------------------------------------------------- //
// ShaderProgram -------------------------------------------------------- //
// ---------------------------------------------------------------------- //
class ShaderProgram {
 public:
  virtual ~ShaderProgram() = default;

  virtual void use() const = 0;
  virtual void unuse() const = 0;

  virtual const std::string &getName() const = 0;
  virtual void setName(const std::string &name) = 0;

  virtual void setUniform(const std::string &name, float value) = 0;
  virtual void setUniform(const std::string &name, Vector2F values) = 0;
  virtual void setUniform(const std::string &name, Vector3F values) = 0;
  virtual void setUniform(const std::string &name, Vector4F values) = 0;
  virtual void setUniform(const std::string &name, Int32 value) = 0;
  virtual void setUniform(const std::string &name, Int32 *values,
                          UInt32 count) = 0;
  virtual void setUniform(const std::string &name, Matrix3F matrix) = 0;
  virtual void setUniform(const std::string &name, Matrix4F matrix) = 0;

  static std::shared_ptr<ShaderProgram> create(const std::string &filepath);
  static std::shared_ptr<ShaderProgram> create(const std::string &name,
                                               const std::string &filepath);
  static std::shared_ptr<ShaderProgram> create(
      const std::string &name, const std::string &vertexSource,
      const std::string &fragmentSource);
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
}  // namespace Neat