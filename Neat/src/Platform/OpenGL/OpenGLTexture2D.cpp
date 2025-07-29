#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLTexture2D.hpp"
#include "Neat/Graphics/Renderer.hpp"
#include "Neat/Utils/LoadImage.hpp"

#include <glad/glad.h>

namespace Neat {
OpenGLTexture2D::OpenGLTexture2D(Int32 width, Int32 height)
    : m_width(width),
      m_height(height),
      m_internalFormat(GL_RGBA8),
      m_dataFormat(GL_RGBA) {
  NT_PROFILE_FUNCTION();
  NT_CORE_ASSERT(m_internalFormat & m_dataFormat,
                 "Color channel format not supported!");

  glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

  // Alocates storage on the gpu for the texture
  glTextureStorage2D(m_id, 1, m_internalFormat, width, m_height);

  // Set linear interpolation (integer parameter) for resizing
  // (expansion or contraction) the texture in the geometry
  glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture2D::OpenGLTexture2D(const std::string &filepath)
    : m_internalFormat(0), m_dataFormat(0) {
  NT_PROFILE_FUNCTION();
  auto result = loadImage(filepath);
  if (not result) {
    NT_CORE_ERROR("Failed to load texture image: {0}", result.error().filepath);
    NT_CORE_ASSERT(false, "");
  }

  const Image &image = *result;
  m_width = image.getWidth();
  m_height = image.getHeight();

  if (image.getChannels() == 4) {
    m_internalFormat = GL_RGBA8;
    m_dataFormat = GL_RGBA;
  } else if (image.getChannels() == 3) {
    m_internalFormat = GL_RGB8;
    m_dataFormat = GL_RGB;
  }

  NT_CORE_ASSERT(m_internalFormat & m_dataFormat,
                 "Color channel format not supported!");

  glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

  // Alocates storage on the gpu for the texture
  glTextureStorage2D(m_id, 1, m_internalFormat, m_width, m_height);

  // Set linear interpolation (integer parameter) for resizing
  // (expansion or contraction) the texture in the geometry
  glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_dataFormat,
                      GL_UNSIGNED_BYTE, image.getData());
  glGenerateMipmap(GL_TEXTURE_2D);
}

OpenGLTexture2D::~OpenGLTexture2D() {
  NT_PROFILE_FUNCTION();
  glDeleteTextures(1, &m_id);
}

void OpenGLTexture2D::setData(void *data, UInt32 size) {
  NT_PROFILE_FUNCTION();
  uint32_t bytesPerPixel = m_dataFormat == GL_RGBA ? 4 : 3;
  NT_CORE_ASSERT(size == m_width * m_height * bytesPerPixel,
                 "Data must be entire texture!");
  glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_dataFormat,
                      GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void OpenGLTexture2D::bind(UInt32 unit) const {
  NT_PROFILE_FUNCTION();
  glBindTextureUnit(unit, m_id);
}
}  // namespace Neat
