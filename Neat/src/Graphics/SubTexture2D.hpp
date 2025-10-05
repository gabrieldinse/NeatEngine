#pragma once

#include "Texture2D.hpp"

namespace Neat {
class SubTexture2D {
 public:
  SubTexture2D(const Ref<Texture2D> &texture,
               const Vector2F &upperLeftCoordinate, const Vector2F &size);

  const Vector2F *getCoordinates() const { return m_textureCoordinates; }

  static Ref<SubTexture2D> createFromIndex(
      const Ref<Texture2D> &texture, const Vector2F &indexes,
      const Vector2F &cellSize, const Vector2F &subTextureSizeInCells = {1, 1});

 private:
  Ref<Texture2D> m_texture;
  Vector2F m_textureCoordinates[4];
};
}  // namespace Neat