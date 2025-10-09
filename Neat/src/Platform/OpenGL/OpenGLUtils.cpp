#include "NeatPCH.hpp"

#include "OpenGLUtils.hpp"

#include <glad/glad.h>

namespace Neat {
namespace OpenGLUtils {
UInt32 toPrimitiveType(ShaderDataType type) {
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
    case ShaderDataType::UInt:
      return GL_UNSIGNED_INT;
    case ShaderDataType::Vector2UI:
      return GL_UNSIGNED_INT;
    case ShaderDataType::Vector3UI:
      return GL_UNSIGNED_INT;
    case ShaderDataType::Vector4UI:
      return GL_UNSIGNED_INT;
    case ShaderDataType::Bool:
      return GL_BOOL;
    default:
      NT_CORE_ASSERT(false, "Unknown or unsupported ShaderDataType!");
      return 0;
  }
}

UInt32 toType(ShaderDataType type) {
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
    case ShaderDataType::UInt:
      return GL_UNSIGNED_INT;
    case ShaderDataType::Vector2UI:
      return GL_UNSIGNED_INT_VEC2;
    case ShaderDataType::Vector3UI:
      return GL_UNSIGNED_INT_VEC3;
    case ShaderDataType::Vector4UI:
      return GL_UNSIGNED_INT_VEC4;
    case ShaderDataType::Bool:
      return GL_BOOL;
    default:
      NT_CORE_ASSERT(false, "Unknown or unsupported ShaderDataType!");
      return 0;
  }

  NT_CORE_ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}

ShaderDataType toShaderDataType(UInt32 type, UInt32 count) {
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

UInt32 getShaderTypeFromString(const std::string &type) {
  if (type == "vertex") return GL_VERTEX_SHADER;

  if (type == "fragment" or type == "pixel") return GL_FRAGMENT_SHADER;

  NT_CORE_ASSERT(false, "Unkown shader type.");
  return 0;
}

Int toTexture2DWrapping(Texture2DWrapping wrapping) {
  switch (wrapping) {
    case Texture2DWrapping::Repeat:
      return GL_REPEAT;
    case Texture2DWrapping::MirroredRepeat:
      return GL_MIRRORED_REPEAT;
    case Texture2DWrapping::ClampToEdge:
      return GL_CLAMP_TO_EDGE;
    case Texture2DWrapping::ClampToBorder:
      return GL_CLAMP_TO_BORDER;
    default:
      NT_CORE_ASSERT(false, "Unknown Texture2DWrapping.");
  }
}

Int toTexture2DFilter(Texture2DFilter filter) {
  switch (filter) {
    case Texture2DFilter::Nearest:
      return GL_NEAREST;
    case Texture2DFilter::Linear:
      return GL_LINEAR;
    case Texture2DFilter::NearestMipmapNearest:
      return GL_NEAREST_MIPMAP_NEAREST;
    case Texture2DFilter::NearestMipmapLinear:
      return GL_NEAREST_MIPMAP_LINEAR;
    case Texture2DFilter::LinearMipmapLinear:
      return GL_LINEAR_MIPMAP_LINEAR;
    case Texture2DFilter::LinearMipmapNearest:
      return GL_LINEAR_MIPMAP_NEAREST;
    default:
      NT_CORE_ASSERT(false, "Unknown Texture2DFilter.");
  }
}

Int getTextureTarget(bool multisampled) {
  return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

Int getFramebufferColorFormat(FramebufferColorFormat colorFormat) {
  switch (colorFormat) {
    case FramebufferColorFormat::RGBA8:
      return GL_RGBA;

    case FramebufferColorFormat::OneUInt32:
      return GL_RED_INTEGER;

    default:
      NT_CORE_ERROR("Invalid framebuffer color format.");
      NT_CORE_ASSERT(false);
      return -1;
  }
}

Int getFramebufferColorInternalFormat(FramebufferColorFormat colorFormat) {
  switch (colorFormat) {
    case FramebufferColorFormat::RGBA8:
      return GL_RGBA8;
    case FramebufferColorFormat::OneUInt32:
      return GL_R32UI;
    default:
      NT_CORE_ERROR("Invalid framebuffer color internal format.");
      NT_CORE_ASSERT(false);
      return -1;
  }
}

Int getFramebufferDepthFormat(FramebufferDepthFormat depthFormat) {
  switch (depthFormat) {
    case FramebufferDepthFormat::Depth24Stencil8:
      return GL_DEPTH24_STENCIL8;

    default:
      NT_CORE_ERROR("Invalid framebuffer depth format.");
      NT_CORE_ASSERT(false);
      return -1;
  }
}

Int getFramebufferDepthAttachmentType(FramebufferDepthFormat depthFormat) {
  switch (depthFormat) {
    case FramebufferDepthFormat::Depth24Stencil8:
      return GL_DEPTH_STENCIL_ATTACHMENT;

    default:
      NT_CORE_ERROR("Invalid framebuffer depth attachment type.");
      NT_CORE_ASSERT(false);
      return -1;
  }
}
}  // namespace OpenGLUtils
}  // namespace Neat