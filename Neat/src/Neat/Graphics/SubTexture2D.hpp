#pragma once

#include "Neat/Graphics/Texture2D.hpp"

namespace Neat {
class SubTexture2D {
 public:
  SubTexture2D(const std::shared_ptr<Texture2D> &texture,
               const Vector2F &upperLeftCoordinate, const Vector2F &size);

  const Vector2F *getCoordinates() const { return m_textureCoordinates; }

  static std::shared_ptr<SubTexture2D> createFromIndex(
      const std::shared_ptr<Texture2D> &texture, const Vector2F &indexes,
      const Vector2F &cellSize, const Vector2F &subTextureSizeInCells = {1, 1});

 private:
  std::shared_ptr<Texture2D> m_texture;
  Vector2F m_textureCoordinates[4];
};
}  // namespace Neat