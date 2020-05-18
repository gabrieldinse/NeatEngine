#pragma once

#include "Neat/Renderer/Texture.h"


namespace Neat
{
   class SubTexture2D : public Texture2D
   {
   public:
      SubTexture2D(const Texture2D& texture,
         const Vector2& upperLeftCoordinate, const Vector2& size);

      virtual const Vector2* getCoordinates() const override
      {
         return m_textureCoordinates;
      }

      static std::shared_ptr<SubTexture2D> createFromIndex(
         const Texture2D& texture,
         const Vector2& indexes, const Vector2& cellSize,
         const Vector2& subTextureSizeInCells = { 1, 1 });

   private:
      Vector2 m_textureCoordinates[4];
   };
}