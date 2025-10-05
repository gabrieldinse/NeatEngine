#pragma once

#include <memory>
#include <string>

#include "Core/Types.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"

namespace Neat {
class ShaderProgram {
 public:
  virtual ~ShaderProgram() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual const std::string &getName() const = 0;
  virtual void setName(const std::string &name) = 0;

  virtual void set(const std::string &name, float value) = 0;
  virtual void set(const std::string &name, Vector2F values) = 0;
  virtual void set(const std::string &name, Vector3F values) = 0;
  virtual void set(const std::string &name, Vector4F values) = 0;
  virtual void set(const std::string &name, Int32 value) = 0;
  virtual void set(const std::string &name, Int32 *values, UInt32 count) = 0;
  virtual void set(const std::string &name, Matrix3F matrix) = 0;
  virtual void set(const std::string &name, Matrix4F matrix) = 0;

  static Ref<ShaderProgram> create(const std::string &filepath);
  static Ref<ShaderProgram> create(const std::string &name,
                                   const std::string &filepath);
  static Ref<ShaderProgram> create(const std::string &name,
                                   const std::string &vertexSource,
                                   const std::string &fragmentSource);
};
}  // namespace Neat