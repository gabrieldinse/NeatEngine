#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include "Neat/Core/Types.hpp"

namespace Neat {
enum class ShaderDataType {
  None = 0,

  Float,
  Vector2F,
  Vector3F,
  Vector4F,
  FloatArray,
  Vector2Array,
  Vector3Array,
  Vector4Array,

  Matrix2F,
  Matrix3F,
  Matrix4F,
  Matrix2Array,
  Matrix3Array,
  Matrix4Array,

  Int,
  Vector2I,
  Vector3I,
  Vector4I,
  IntArray,
  IVector2Array,
  IVector3Array,
  IVector4Array,

  Bool
};

class OpenGLTypeConverter {
 public:
  static UInt32 sizeInBytes(ShaderDataType type);
  static UInt32 componentCount(ShaderDataType type);
  static UInt32 baseType(ShaderDataType type);
  static UInt32 type(ShaderDataType type);
  static ShaderDataType toShaderDataType(UInt32 type, UInt32 count);
  static UInt32 fromStringToShaderType(const std::string &type);
};
}  // namespace Neat