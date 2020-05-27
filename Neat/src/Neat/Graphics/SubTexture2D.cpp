#include "Neat/Graphics/SubTexture2D.h"


namespace Neat
{
   SubTexture2D::SubTexture2D(const Texture2D& texture,
      const Vector2& bottomLeftCoordinate, const Vector2& upperRightCoordinate)
      : Texture2D(texture)
      , m_textureCoordinates{
         bottomLeftCoordinate,
         {upperRightCoordinate.x, bottomLeftCoordinate.y},
         upperRightCoordinate,
         {bottomLeftCoordinate.x, upperRightCoordinate.y}
      }
   {
   }

   std::shared_ptr<SubTexture2D> SubTexture2D::createFromIndex(
      const Texture2D& texture, const Vector2& indexes,
      const Vector2& cellSize, const Vector2& subTextureSizeInCells)
   {
      Vector2 bottom_left_coordinate(
         indexes.i * cellSize.x / texture.getWidth(),
         indexes.j * cellSize.y / texture.getHeight()
      );
      Vector2 upper_right_coordinate(
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