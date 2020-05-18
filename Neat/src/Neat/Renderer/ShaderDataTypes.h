#pragma once

#include <cstdint>
#include <cstddef>

#include "Neat/Core/Types.h"


namespace Neat
{
   enum class ShaderDataType
   {
      None = 0,
      Float, Vector2, Vector3, Vector4,
      Matrix3, Matrix4, Int, Int2, Int3, Int4,
      Bool,
      Sampler2DArray,
      IntArray
   };

   UInt shaderDataTypeSize(ShaderDataType type);
   UInt shaderDataTypeComponentCount(ShaderDataType type);
   UInt shaderDataTypeToOpenGLBaseType(ShaderDataType type);
   UInt shaderDataTypeToOpenGLType(ShaderDataType type);
   ShaderDataType openGLTypeToShaderDataType(UInt type, Int count);
}