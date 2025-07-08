#include "NeatPCH.hpp"

#include "Platform/OpenGL/OpenGLTexture2D.hpp"
#include "Neat/Graphics/Renderer.hpp"

#include <glad/glad.h>
#include <stb_image.h>

namespace Neat {
OpenGLTexture2D::OpenGLTexture2D(Int32 width, Int32 height)
    : m_width(width),
      m_height(height),
      m_internalFormat(GL_RGBA8),
      m_dataFormat(GL_RGBA) {
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
  // stbi_load uses signed Int32
  Int32 width, height, channels;
  stbi_set_flip_vertically_on_load(1);  // flip the image loaded vertically
  auto data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
  NT_CORE_ASSERT(data, "Failed to load texture image!");

  // Converts to unsigned because OpenGL uses UInt32
  m_width = width;
  m_height = height;

  if (channels == 4) {
    m_internalFormat = GL_RGBA8;
    m_dataFormat = GL_RGBA;
  } else if (channels == 3) {
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
                      GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Deallocates the memory
  stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D() { glDeleteTextures(1, &m_id); }

void OpenGLTexture2D::setData(void *data, UInt32 size) {
  glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_dataFormat,
                      GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void OpenGLTexture2D::bind(UInt32 unit) const { glBindTextureUnit(unit, m_id); }
}  // namespace Neat
