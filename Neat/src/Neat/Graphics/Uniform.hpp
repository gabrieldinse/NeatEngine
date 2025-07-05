#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Neat/Core/PlatformDetection.hpp"
#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/ShaderDataType.hpp"
#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
template <ShaderDataType UniformType>
struct Uniform;
struct UniformData;
class ShaderProgram;

// ---------------------------------------------------------------------- //
// UniformLibrary-------------------------------------------------------- //
// ---------------------------------------------------------------------- //
class UniformLibrary {
 public:
  UniformLibrary(ShaderProgram &shader);
  UniformLibrary() = delete;
  ~UniformLibrary();

  bool exists(const std::string &name) const;

  UniformData &operator[](const std::string &name);
  const UniformData &operator[](const std::string &name) const;

 private:
  std::unordered_map<std::string, std::unique_ptr<UniformData>> m_uniforms;
  ShaderProgram &m_shader;
};

// ---------------------------------------------------------------------- //
// UniformBase ---------------------------------------------------------- //
// ---------------------------------------------------------------------- //
class UniformBase {
 public:
  virtual ~UniformBase();

  const std::string &getName() const;
  Int32 getType() const;
  Int32 getSize() const;
  Int32 getLocation() const;

 protected:
  void checkUniform(ShaderDataType uniformType, const std::string &name,
                    const UniformLibrary &uniformLibrary);

 protected:
  std::unique_ptr<UniformData> m_data;
};

// ---------------------------------------------------------------------- //
// Uniform -------------------------------------------------------------- //
// ---------------------------------------------------------------------- //
template <ShaderDataType uniformType>
struct Uniform : public UniformBase {};

template <>
struct Uniform<ShaderDataType::Float> : public UniformBase {
  void set(float value);

 private:
  friend class ShaderProgram;
  Uniform(const std::string &name, const UniformLibrary &uniformLibrary);
};

template <>
struct Uniform<ShaderDataType::Vector2F> : public UniformBase {
  void set(Vector2F values);

 private:
  friend class ShaderProgram;
  Uniform(const std::string &name, const UniformLibrary &uniformLibrary);
};

template <>
struct Uniform<ShaderDataType::Vector3F> : public UniformBase {
  void set(Vector3F values);

 private:
  friend class ShaderProgram;
  Uniform(const std::string &name, const UniformLibrary &uniformLibrary);
};

template <>
struct Uniform<ShaderDataType::Vector4F> : public UniformBase {
  void set(Vector4F values);

 private:
  friend class ShaderProgram;
  Uniform(const std::string &name, const UniformLibrary &uniformLibrary);
};

template <>
struct Uniform<ShaderDataType::Int> : public UniformBase {
  void set(Int32 value);

 private:
  friend class ShaderProgram;
  Uniform(const std::string &name, const UniformLibrary &uniformLibrary);
};

template <>
struct Uniform<ShaderDataType::IntArray> : public UniformBase {
  void set(Int32 *values, UInt32 count);

 private:
  friend class ShaderProgram;
  Uniform(const std::string &name, const UniformLibrary &uniformLibrary);
};

template <>
struct Uniform<ShaderDataType::Matrix3F> : public UniformBase {
  void set(Matrix3F matrix);

 private:
  friend class ShaderProgram;
  Uniform(const std::string &name, const UniformLibrary &uniformLibrary);
};

template <>
struct Uniform<ShaderDataType::Matrix4F> : public UniformBase {
  void set(Matrix4F matrix);

 private:
  friend class ShaderProgram;
  Uniform(const std::string &name, const UniformLibrary &uniformLibrary);
};
}  // namespace Neat