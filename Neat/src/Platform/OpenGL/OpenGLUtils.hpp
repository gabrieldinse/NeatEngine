#pragma once

#include "Graphics/ShaderDataType.hpp"
#include "Graphics/Texture2D.hpp"
#include "Graphics/Framebuffer.hpp"

namespace Neat {

namespace OpenGLUtils {
UInt32 toPrimitiveType(ShaderDataType type);
UInt32 toType(ShaderDataType type);
ShaderDataType toShaderDataType(UInt32 type, UInt32 count);
UInt32 getShaderTypeFromString(const std::string &type);
Int toTexture2DWrapping(Texture2DWrapping wrapping);
Int toTexture2DFilter(Texture2DFilter filter);
Int getTextureTarget(bool multisampled);
Int getFramebufferColorFormat(FramebufferColorFormat colorFormat);
Int getFramebufferColorInternalFormat(FramebufferColorFormat depthFormat);
Int getFramebufferDepthFormat(FramebufferDepthFormat depthFormat);
Int getFramebufferDepthAttachmentType(FramebufferDepthFormat depthFormat);
}  // namespace OpenGLUtils
}  // namespace Neat