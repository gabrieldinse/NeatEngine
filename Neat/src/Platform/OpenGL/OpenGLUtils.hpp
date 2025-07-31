#pragma once

#include "Neat/Graphics/ShaderDataType.hpp"
#include "Neat/Graphics/Texture2D.hpp"

namespace Neat {

namespace OpenGL {
UInt32 getPrimitiveType(ShaderDataType type);
UInt32 getType(ShaderDataType type);
ShaderDataType getShaderDataType(UInt32 type, UInt32 count);
UInt32 getShaderDataType(const std::string &type);
Int getTexture2DWrapping(Texture2DWrapping wrapping);
Int getTexture2DFilter(Texture2DFilter filter);
}  // namespace OpenGL
}  // namespace Neat