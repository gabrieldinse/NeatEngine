#pragma once

#include "Neat/Graphics/Renderer2D.h"
#include "Neat/Graphics/Shapes2D/Shape.h"


namespace Neat
{
   class Quad : public Shape
   {
   public:
      Quad(const Vector3& position = { 0.0f, 0.0f, 0.0f },
         const Vector2& size = { 1.0f, 1.0f },
         const Vector4 color = { 1.0f, 0.0f, 1.0f, 1.0f })
         : m_position(position)
         , m_size(size)
         , m_color(color) {}

      void draw() const
      {
         Renderer2D::drawQuad(m_position, m_size, m_color);
      }

   private:
      Vector3 m_position;
      Vector2 m_size;
      Vector4 m_color;
   };
}