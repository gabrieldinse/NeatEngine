#pragma once

#include "Neat/Graphics/ShaderDataType.hpp"

namespace Neat {

class OpenGLTypeConverter {
 public:
  static UInt32 getPrimitiveType(ShaderDataType type);
  static UInt32 getType(ShaderDataType type);
  static ShaderDataType getShaderDataType(UInt32 type, UInt32 count);
  static UInt32 getShaderDataType(const std::string &type);
};
}  // namespace Neat