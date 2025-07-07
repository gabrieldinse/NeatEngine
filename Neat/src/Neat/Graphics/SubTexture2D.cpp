#include "NeatPCH.hpp"

#include "Neat/Graphics/SubTexture2D.hpp"

namespace Neat {
SubTexture2D::SubTexture2D(const std::shared_ptr<Texture2D> &texture,
                           const Vector2F &bottomLeftCoordinate,
                           const Vector2F &upperRightCoordinate)
    : m_texture(texture),
      m_textureCoordinates{bottomLeftCoordinate,
                           {upperRightCoordinate.x, bottomLeftCoordinate.y},
                           upperRightCoordinate,
                           {bottomLeftCoordinate.x, upperRightCoordinate.y}} {}

std::shared_ptr<SubTexture2D> SubTexture2D::createFromIndex(
    const std::shared_ptr<Texture2D> &texture, const Vector2F &indexes,
    const Vector2F &cellSize, const Vector2F &subTextureSizeInCells) {
  Vector2F bottom_left_coordinate(
      indexes.i * cellSize.x / texture->getWidth(),
      indexes.j * cellSize.y / texture->getHeight());
  Vector2F upper_right_coordinate(
      (indexes.i + subTextureSizeInCells.x) * cellSize.x / texture->getWidth(),
      (indexes.j + subTextureSizeInCells.y) * cellSize.y /
          texture->getHeight());

  return std::make_shared<SubTexture2D>(texture, bottom_left_coordinate,
                                        upper_right_coordinate);
}
}  // namespace Neat