#include "NeatPCH.hpp"

#include "Neat/Graphics/ShaderDataType.hpp"

#include <glad/glad.h>

namespace Neat {
UInt32 getShaderDataTypeSize(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float:
      return 4;
    case ShaderDataType::Vector2F:
      return 4 * 2;
    case ShaderDataType::Vector3F:
      return 4 * 3;
    case ShaderDataType::Vector4F:
      return 4 * 4;
    case ShaderDataType::Matrix3F:
      return 4 * 3 * 3;
    case ShaderDataType::Matrix4F:
      return 4 * 4 * 4;
    case ShaderDataType::Int:
      return 4;
    case ShaderDataType::Vector2I:
      return 4 * 2;
    case ShaderDataType::Vector3I:
      return 4 * 3;
    case ShaderDataType::Vector4I:
      return 4 * 4;
    case ShaderDataType::Bool:
      return 4;
  }

  NT_CORE_ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}

UInt32 getShaderDataTypeComponentCount(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float:
      return 1;
    case ShaderDataType::Vector2F:
      return 2;
    case ShaderDataType::Vector3F:
      return 3;
    case ShaderDataType::Vector4F:
      return 4;
    case ShaderDataType::Matrix3F:
      return 3 * 3;
    case ShaderDataType::Matrix4F:
      return 4 * 4;
    case ShaderDataType::Int:
      return 1;
    case ShaderDataType::Vector2I:
      return 2;
    case ShaderDataType::Vector3I:
      return 3;
    case ShaderDataType::Vector4I:
      return 4;
    case ShaderDataType::Bool:
      return 1;
  }

  NT_CORE_ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}
}  // namespace Neat