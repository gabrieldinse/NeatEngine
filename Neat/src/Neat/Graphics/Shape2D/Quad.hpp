#pragma once

#include "Neat/Graphics/Renderer2D.hpp"
#include "Neat/Graphics/Shape2D/Shape.hpp"

namespace Neat {
class Quad : public Shape {
public:
  Quad(const Vector3F &position = {0.0f, 0.0f, 0.0f},
       const Vector2F &size = {1.0f, 1.0f},
       const Vector4F color = {1.0f, 0.0f, 1.0f, 1.0f})
      : m_position(position), m_size(size), m_color(color) {}

  virtual void draw() const override {
    Renderer2D::drawQuad(m_position, m_size, m_color);
  }

private:
  Vector3F m_position;
  Vector2F m_size;
  Vector4F m_color;
};
} // namespace Neat