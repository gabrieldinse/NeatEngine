#include "Neat/Renderer/OrthographicCamera.h"
#include "Neat/Core/Log.h"
#include "Neat/Debug/Instrumentator.h"
#include "Neat/Math/Transforms.h"
#include "Neat/Math/MatrixOperations.h"
#include "Neat/Math/Utility.h"


namespace Neat
{
   OrthographicCamera::OrthographicCamera(Float left, Float right, Float bottom, Float top)
      : projectionMatrix(orthographic(left, right, bottom, top, -1.0f, 1.0f))
      , viewMatrix(1.0f)
      , viewProjectionMatrix(this->projectionMatrix * this->viewMatrix)
   {
      NT_PROFILE_FUNCTION();
   }

   void OrthographicCamera::setProjection(Float left, Float right, Float bottom, Float top)
   {
      NT_PROFILE_FUNCTION();

      this->projectionMatrix = orthographic(left, right, bottom, top, -1.0f, 1.0f);
      this->viewProjectionMatrix = this->projectionMatrix * this->viewMatrix;
   }

   void OrthographicCamera::setPosition(const Vec3& position)
   {
      NT_PROFILE_FUNCTION();

      this->position = position;
      this->recalculateViewMatrix();
   }

   void OrthographicCamera::setRotation(Float rotation)
   {
      NT_PROFILE_FUNCTION();

      this->rotation = rotation;
      this->recalculateViewMatrix();
   }

   void OrthographicCamera::recalculateViewMatrix()
   {
      NT_PROFILE_FUNCTION();

      Mat4 transform =
         translate(this->position) * 
         rotate(degreesToRadians(this->rotation), { 0, 0, 1});

      this->viewMatrix = inverse(transform);
      this->viewProjectionMatrix = this->projectionMatrix * this->viewMatrix;
   }
}