#pragma once

#include "Neat/Graphics/Texture2D.hpp"
#include "Neat/Graphics/Color.hpp"

namespace Neat {
struct RenderableSpriteComponent {
  Ref<Texture2D> texture;
  Vector4F color{Color::magenta};
  float tilingFactor{1.0f};

  RenderableSpriteComponent() = default;
  RenderableSpriteComponent(const RenderableSpriteComponent &other) = default;
  RenderableSpriteComponent(const Ref<Texture2D> &texture,
                            const Vector4F &color = Color::magenta,
                            float tilingFactor = 1.0f)
      : texture(texture), color(color), tilingFactor(tilingFactor) {}
  RenderableSpriteComponent(const Vector4F &color) : color(color) {}
};
}  // namespace Neat