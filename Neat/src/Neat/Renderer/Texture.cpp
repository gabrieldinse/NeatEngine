#include "Neat/Renderer/Texture.h"
#include "Neat/Renderer/Renderer.h"
#include "Neat/Core/Log.h"
#include "Neat/Debug/Instrumentator.h"

#include <stb_image.h>
#include <glad/glad.h>


namespace Neat
{
   Texture2D::Texture2D(Int width, Int height)
      : m_width(width), m_height(height), m_internalFormat(GL_RGBA8), m_dataFormat(GL_RGBA)
   {
      NT_PROFILE_FUNCTION();

      NT_CORE_ASSERT(m_internalFormat & m_dataFormat,
         "Color channel format not supported!");

      glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

      // Alocates storage on the gpu for the texture
      glTextureStorage2D(
         m_id, 1, m_internalFormat, width, m_height);

      // Set linear interpolation (integer parameter) for resizing
      // (expansion or contraction) the texture in the geometry
      glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
   }

   Texture2D::Texture2D(const std::string& filepath)
      : m_internalFormat(0), m_dataFormat(0)
   {
      NT_PROFILE_FUNCTION();

      // stbi_load uses signed Int
      Int width, height, channels;
      stbi_set_flip_vertically_on_load(1); // flip the image loaded vertically
      auto data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
      NT_CORE_ASSERT(data, "Failed to load texture image!");

      // Converts to unsigned because OpenGL uses UInt
      m_width = width;
      m_height = height;

      if (channels == 4)
      {
         m_internalFormat = GL_RGBA8;
         m_dataFormat = GL_RGBA;
      }
      else if (channels == 3)
      {
         m_internalFormat = GL_RGB8;
         m_dataFormat = GL_RGB;
      }

      NT_CORE_ASSERT(m_internalFormat & m_dataFormat,
         "Color channel format not supported!");

      glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

      // Alocates storage on the gpu for the texture
      glTextureStorage2D(
         m_id, 1, m_internalFormat, m_width, m_height);

      // Set linear interpolation (integer parameter) for resizing
      // (expansion or contraction) the texture in the geometry
      glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

      glTextureSubImage2D(
         m_id, 0, 0, 0, m_width, m_height,
         m_dataFormat, GL_UNSIGNED_BYTE, data);

      // Deallocates the memory
      stbi_image_free(data);
   }

   Texture2D::~Texture2D()
   {
      NT_PROFILE_FUNCTION();

      glDeleteTextures(1, &m_id);
   }

   void Texture2D::setData(void* data, UInt size)
   {
      NT_PROFILE_FUNCTION();

      glTextureSubImage2D(
         m_id, 0, 0, 0, m_width, m_height,
         m_dataFormat, GL_UNSIGNED_BYTE, data);
   }

   void Texture2D::bind(UInt slot) const
   {
      NT_PROFILE_FUNCTION();

      glBindTextureUnit(slot, m_id);
   }
}
