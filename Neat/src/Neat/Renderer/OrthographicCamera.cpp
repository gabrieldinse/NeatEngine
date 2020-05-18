#include "Neat/Renderer/OrthographicCamera.h"
#include "Neat/Core/Log.h"
#include "Neat/Debug/Instrumentator.h"
#include "Neat/Math/Transforms.h"
#include "Neat/Math/MatrixOperations.h"
#include "Neat/Math/Utility.h"


namespace Neat
{
   OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
      : m_projectionMatrix(orthographic(left, right, bottom, top, -1.0f, 1.0f))
      , m_viewMatrix(1.0f)
      , m_viewProjectionMatrix(m_projectionMatrix * m_viewMatrix)
   {
      NT_PROFILE_FUNCTION();
   }

   void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
   {
      NT_PROFILE_FUNCTION();

      m_projectionMatrix = orthographic(left, right, bottom, top, -1.0f, 1.0f);
      m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
   }

   void OrthographicCamera::setPosition(const Vector3& position)
   {
      NT_PROFILE_FUNCTION();

      m_position = position;
      recalculateViewMatrix();
   }

   void OrthographicCamera::setRotation(float rotation)
   {
      NT_PROFILE_FUNCTION();

      m_rotation = rotation;
      recalculateViewMatrix();
   }

   void OrthographicCamera::recalculateViewMatrix()
   {
      NT_PROFILE_FUNCTION();

      Matrix4 transform =
         translate(m_position) * 
         rotate(degreesToRadians(m_rotation), { 0, 0, 1});

      m_viewMatrix = inverse(transform);
      m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
   }
}