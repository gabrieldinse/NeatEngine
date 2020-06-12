#pragma once

#include <cstdint>
#include <cstddef>
#include <string>

#include "Neat/Core/Types.h"


namespace Neat
{
   enum class ShaderDataType
   {
      None = 0,

      Float, Vector2, Vector3, Vector4,
      FloatArray, Vector2Array, Vector3Array, Vector4Array,

      Matrix2, Matrix3, Matrix4,
      Matrix2Array, Matrix3Array, Matrix4Array,

      Int, IVector2, IVector3, IVector4,
      IntArray, IVector2Array, IVector3Array, IVector4Array,

      Bool
   };


   class OpenGLTypeConverter
   {
   public:
      static UInt32 sizeInBytes(ShaderDataType type);
      static UInt32 componentCount(ShaderDataType type);
      static UInt32 baseType(ShaderDataType type);
      static UInt32 type(ShaderDataType type);
      static ShaderDataType toShaderDataType(UInt32 type, UInt32 count);
      static UInt32 fromStringToShaderType(const std::string& type);
   };
}