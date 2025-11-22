#pragma once

#include "Core/Types.hpp"

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

  UInt,
  Vector2UI,
  Vector3UI,
  Vector4UI,

  Bool
};

UInt32 getShaderDataTypeSize(ShaderDataType type);
UInt32 getShaderDataTypeComponentCount(ShaderDataType type);
}  // namespace Neat