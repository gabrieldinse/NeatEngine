#pragma once

#include "Neat/Graphics/Texture.hpp"

namespace Neat {
class SubTexture2D : public Texture2D {
public:
  SubTexture2D(const Texture2D &texture, const Vector2F &upperLeftCoordinate,
               const Vector2F &size);

  virtual const Vector2F *getCoordinates() const override {
    return m_textureCoordinates;
  }

  static std::shared_ptr<SubTexture2D>
  createFromIndex(const Texture2D &texture, const Vector2F &indexes,
                  const Vector2F &cellSize,
                  const Vector2F &subTextureSizeInCells = {1, 1});

private:
  Vector2F m_textureCoordinates[4];
};
} // namespace Neat