#pragma once

#include "Graphics/ShaderDataType.hpp"
#include "Graphics/Texture2D.hpp"
#include "Graphics/Framebuffer.hpp"

namespace Neat {

namespace OpenGL {
UInt32 getPrimitiveType(ShaderDataType type);
UInt32 getType(ShaderDataType type);
ShaderDataType getShaderDataType(UInt32 type, UInt32 count);
UInt32 getShaderDataType(const std::string &type);
Int getTexture2DWrapping(Texture2DWrapping wrapping);
Int getTexture2DFilter(Texture2DFilter filter);
Int getTextureTarget(bool multisampled);
Int getFramebufferColorFormat(FramebufferColorFormat colorFormat);
Int getFramebufferColorInternalFormat(FramebufferColorFormat depthFormat);
Int getFramebufferDepthFormat(FramebufferDepthFormat depthFormat);
Int getFramebufferDepthAttachmentType(FramebufferDepthFormat depthFormat);
}  // namespace OpenGL
}  // namespace Neat