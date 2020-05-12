#pragma once

#include "Neat/Renderer/Texture.h"


namespace Neat
{
   class SubTexture2D : public Texture2D
   {
   public:
      SubTexture2D(const Texture2D& texture,
         const Vec2& upperLeftCoordinate, const Vec2& size);

      virtual const Vec2* getCoordinates() const override
      {
         return this->textureCoordinates;
      }

      static std::shared_ptr<SubTexture2D> createFromIndex(
         const Texture2D& texture,
         const Vec2& indexes, const Vec2& cellSize,
         const Vec2& subTextureSizeInCells = { 1, 1 });

   private:
      Vec2 textureCoordinates[4];
   };
}