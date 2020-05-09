#include "Neat/Renderer/SubTexture2D.h"


namespace Neat
{
   SubTexture2D::SubTexture2D(const Texture2D& texture,
      const Vec2& bottomLeftCoordinate, const Vec2& upperRightCoordinate)
      : Texture2D(texture)
      , textureCoordinates{
         bottomLeftCoordinate,
         {upperRightCoordinate.x, bottomLeftCoordinate.y},
         upperRightCoordinate,
         {bottomLeftCoordinate.x, upperRightCoordinate.y}
      }
   {
   }

   std::shared_ptr<SubTexture2D> SubTexture2D::createFromIndex(
      const Texture2D& texture, const Vec2& indexes,
      const Vec2& cellSize, const Vec2& subTextureSizeInCells)
   {
      Vec2 bottom_left_coordinate(
         indexes.i * cellSize.x / texture.getWidth(),
         indexes.j * cellSize.y / texture.getHeight()
      );
      Vec2 upper_right_coordinate(
         (indexes.i + subTextureSizeInCells.x) * cellSize.x / texture.getWidth(),
         (indexes.j + subTextureSizeInCells.y) * cellSize.y / texture.getHeight()
      );

      return std::make_shared<SubTexture2D>(
         texture,
         bottom_left_coordinate,
         upper_right_coordinate
         );
   }
}