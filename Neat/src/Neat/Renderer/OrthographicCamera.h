#pragma once

#include "Neat/Math/Matrix.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class OrthographicCamera
   {
   public:
      OrthographicCamera(float left, float right, float bottom, float top);
      void setProjection(float left, float right, float bottom, float top);
      
      const Vec3& getPosition() const { return m_position; }
      float getRotation() const { return m_rotation; }
      void setPosition(const Vec3& position);
      void setRotation(float rotation);

      const Mat4& getProjectionMatrix() const { return m_projectionMatrix; }
      const Mat4& getViewMatrix() const { return m_viewMatrix; }
      const Mat4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

   private:
      void recalculateViewMatrix();

   private:
      Mat4 m_projectionMatrix;
      Mat4 m_viewMatrix;
      Mat4 m_viewProjectionMatrix;
      Vec3 m_position = {0.0f, 0.0f, 0.0f};
      float m_rotation = 0.0f;
   };
}