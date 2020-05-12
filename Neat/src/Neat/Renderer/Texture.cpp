#include "Neat/Renderer/Texture.h"
#include "Neat/Renderer/Renderer.h"
#include "Neat/Core/Log.h"
#include "Neat/Debug/Instrumentator.h"

#include <stb_image.h>
#include <glad/glad.h>


namespace Neat
{
   Texture2D::Texture2D(Int width, Int height)
      : width(width), height(height), internalFormat(GL_RGBA8), dataFormat(GL_RGBA)
   {
      NT_PROFILE_FUNCTION();

      NT_CORE_ASSERT(this->internalFormat & this->dataFormat,
         "Color channel format not supported!");

      glCreateTextures(GL_TEXTURE_2D, 1, &this->id);

      // Alocates storage on the gpu for the texture
      glTextureStorage2D(
         this->id, 1, this->internalFormat, this->width, this->height);

      // Set linear interpolation (integer parameter) for resizing
      // (expansion or contraction) the texture in the geometry
      glTextureParameteri(this->id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(this->id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTextureParameteri(this->id, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTextureParameteri(this->id, GL_TEXTURE_WRAP_T, GL_REPEAT);
   }

   Texture2D::Texture2D(const std::string& filepath)
      : internalFormat(0), dataFormat(0)
   {
      NT_PROFILE_FUNCTION();

      // stbi_load uses signed Int
      Int width, height, channels;
      stbi_set_flip_vertically_on_load(1); // flip the image loaded vertically
      auto data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
      NT_CORE_ASSERT(data, "Failed to load texture image!");

      // Converts to unsigned because OpenGL uses UInt
      this->width = width;
      this->height = height;

      if (channels == 4)
      {
         this->internalFormat = GL_RGBA8;
         this->dataFormat = GL_RGBA;
      }
      else if (channels == 3)
      {
         this->internalFormat = GL_RGB8;
         this->dataFormat = GL_RGB;
      }

      NT_CORE_ASSERT(this->internalFormat & this->dataFormat,
         "Color channel format not supported!");

      glCreateTextures(GL_TEXTURE_2D, 1, &this->id);

      // Alocates storage on the gpu for the texture
      glTextureStorage2D(
         this->id, 1, this->internalFormat, this->width, this->height);

      // Set linear interpolation (integer parameter) for resizing
      // (expansion or contraction) the texture in the geometry
      glTextureParameteri(this->id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTextureParameteri(this->id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTextureParameteri(this->id, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTextureParameteri(this->id, GL_TEXTURE_WRAP_T, GL_REPEAT);

      glTextureSubImage2D(
         this->id, 0, 0, 0, this->width, this->height,
         this->dataFormat, GL_UNSIGNED_BYTE, data);

      // Deallocates the memory
      stbi_image_free(data);
   }

   Texture2D::~Texture2D()
   {
      NT_PROFILE_FUNCTION();

      glDeleteTextures(1, &this->id);
   }

   void Texture2D::setData(void* data, UInt size)
   {
      NT_PROFILE_FUNCTION();

      glTextureSubImage2D(
         this->id, 0, 0, 0, this->width, this->height,
         this->dataFormat, GL_UNSIGNED_BYTE, data);
   }

   void Texture2D::bind(UInt slot) const
   {
      NT_PROFILE_FUNCTION();

      glBindTextureUnit(slot, this->id);
   }
}
