#pragma once

#include "Neat/Math/Matrix.h"
#include "Neat/Math/Vector.h"


namespace Neat
{
   class OrthographicCamera
   {
   public:
      OrthographicCamera(Float left, Float right, Float bottom, Float top);
      void setProjection(Float left, Float right, Float bottom, Float top);
      
      const Vec3& getPosition() const { return this->position; }
      Float getRotation() const { return this->rotation; }
      void setPosition(const Vec3& position);
      void setRotation(Float rotation);

      const Mat4& getProjectionMatrix() const { return this->projectionMatrix; }
      const Mat4& getViewMatrix() const { return this->viewMatrix; }
      const Mat4& getViewProjectionMatrix() const { return this->viewProjectionMatrix; }

   private:
      void recalculateViewMatrix();

   private:
      Mat4 projectionMatrix;
      Mat4 viewMatrix;
      Mat4 viewProjectionMatrix;
      Vec3 position = {0.0f, 0.0f, 0.0f};
      Float rotation = 0.0f;
   };
}