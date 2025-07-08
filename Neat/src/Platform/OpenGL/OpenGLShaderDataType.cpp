#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLShaderDataType.hpp"

#include <glad/glad.h>

namespace Neat {
UInt32 OpenGLTypeConverter::getPrimitiveType(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float:
      return GL_FLOAT;
    case ShaderDataType::Vector2F:
      return GL_FLOAT;
    case ShaderDataType::Vector3F:
      return GL_FLOAT;
    case ShaderDataType::Vector4F:
      return GL_FLOAT;
    case ShaderDataType::Matrix3F:
      return GL_FLOAT;
    case ShaderDataType::Matrix4F:
      return GL_FLOAT;
    case ShaderDataType::Int:
      return GL_INT;
    case ShaderDataType::Vector2I:
      return GL_INT;
    case ShaderDataType::Vector3I:
      return GL_INT;
    case ShaderDataType::Vector4I:
      return GL_INT;
    case ShaderDataType::Bool:
      return GL_BOOL;
    default:
      NT_CORE_ASSERT(false, "Unknown or unsupported ShaderDataType!");
      return 0;
  }
}

UInt32 OpenGLTypeConverter::getType(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float:
      return GL_FLOAT;
    case ShaderDataType::Vector2F:
      return GL_FLOAT_VEC2;
    case ShaderDataType::Vector3F:
      return GL_FLOAT_VEC3;
    case ShaderDataType::Vector4F:
      return GL_FLOAT_VEC4;
    case ShaderDataType::Matrix3F:
      return GL_FLOAT_MAT3;
    case ShaderDataType::Matrix4F:
      return GL_FLOAT_MAT4;
    case ShaderDataType::Int:
      return GL_INT;
    case ShaderDataType::Vector2I:
      return GL_INT_VEC2;
    case ShaderDataType::Vector3I:
      return GL_INT_VEC3;
    case ShaderDataType::Vector4I:
      return GL_INT_VEC4;
    case ShaderDataType::Bool:
      return GL_BOOL;
    default:
      NT_CORE_ASSERT(false, "Unknown or unsupported ShaderDataType!");
      return 0;
  }

  NT_CORE_ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}

ShaderDataType OpenGLTypeConverter::getShaderDataType(UInt32 type,
                                                      UInt32 count) {
  switch (type) {
    case GL_FLOAT: {
      if (count == 1) return ShaderDataType::Float;
      break;
    }

    case GL_FLOAT_VEC2: {
      if (count == 1) return ShaderDataType::Vector2F;
      break;
    }

    case GL_FLOAT_VEC3: {
      if (count == 1) return ShaderDataType::Vector3F;
      break;
    }

    case GL_FLOAT_VEC4: {
      if (count == 1) return ShaderDataType::Vector4F;
      break;
    }

    case GL_FLOAT_MAT3: {
      if (count == 1) return ShaderDataType::Matrix3F;
      break;
    }

    case GL_FLOAT_MAT4: {
      if (count == 1) return ShaderDataType::Matrix4F;
      break;
    }

    case GL_INT: {
      if (count == 1) return ShaderDataType::Int;
      break;
    }

    case GL_SAMPLER_2D: {
      if (count == 1) return ShaderDataType::Int;
      if (count > 1) return ShaderDataType::IntArray;
      break;
    }
    default:
      NT_CORE_ASSERT(false, "Unknown uniform type!");
      return ShaderDataType::None;
  }
  NT_CORE_ASSERT(false, "Unknown uniform type!");
  return ShaderDataType::None;
}

UInt32 OpenGLTypeConverter::getShaderDataType(const std::string &type) {
  if (type == "vertex") return GL_VERTEX_SHADER;

  if (type == "fragment" or type == "pixel") return GL_FRAGMENT_SHADER;

  NT_CORE_ASSERT(false, "Unkown shader type.");
  return 0;
}
}  // namespace Neat