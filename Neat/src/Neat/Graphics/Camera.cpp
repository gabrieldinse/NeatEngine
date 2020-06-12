#include <cmath>

#include "Neat/Core/Log.h"
#include "Neat/Graphics/Camera.h"
#include "Neat/Math/Transform.h"
#include "Neat/Math/Projection.h"
#include "Neat/Math/MatrixOperations.h"
#include "Neat/Math/Utility.h"


namespace Neat
{
   Camera::Camera(const Vector3& position, const Vector3& up, float pitch,
      float yaw, float roll)
      : m_cameraType(CameraType::None)
      , m_position(position)
      , m_worldUp(normalize(up))
      , m_pitch(pitch)
      , m_yaw(yaw)
      , m_roll(roll)
   {
      updateOrientationVectors();
   }


   Camera& Camera::setOrthographic(float left, float right, float bottom,
      float top, float near, float far)
   {
      m_cameraData = OrthographicCameraProperties(
         left, right, bottom, top, near, far);
      m_cameraType = CameraType::Orthographic;

      return *this;
   }

   Camera& Camera::setPerspective(float fov, float aspectRatio, float near,
      float far)
   {
      m_cameraData = PerspectiveCameraProperties(fov, aspectRatio, near, far);
      m_cameraType = CameraType::Perspective;

      return *this;
   }

   void Camera::setRotation(float pitch, float yaw, float roll)
   {
      m_pitch = pitch;
      m_yaw = yaw;
      m_roll = roll;
      updateOrientationVectors();
   }

   void Camera::setYaw(float yaw)
   {
      m_yaw = yaw;
      updateOrientationVectors();
   }
   void Camera::setPitch(float pitch)
   {
      m_pitch = pitch;
      updateOrientationVectors();
   }

   void Camera::setRoll(float roll)
   {
      m_roll = roll;
      updateOrientationVectors();
   }


   Matrix4 Camera::getProjectionMatrix() const
   {
      switch (m_cameraType)
      {
         case CameraType::Orthographic:
         {
            auto camera_data = getOrthographicData();
            return orthographic(camera_data.left, camera_data.right,
                  camera_data.bottom, camera_data.top, camera_data.near,
                  camera_data.far);
         }
         case CameraType::Perspective:
         {
            auto camera_data = getPerspectiveData();
            return perspective(camera_data.fieldOfView,
               camera_data.aspectRatio, camera_data.near, camera_data.far);
         }
         default:
            NT_CORE_ASSERT(false, "Unknown camera type.");
            return Matrix4();
      }
   }

   Matrix4 Camera::getViewMatrix() const
   {
      return lookAtRH(m_position, m_position + m_front, m_up);
   }

   Matrix4 Camera::getCameraTransform() const
   {
      return getProjectionMatrix() * getViewMatrix();
   }

   void Camera::updateOrientationVectors()
   {
      Vector3 front(
         cos(radians(m_yaw)) * cos(radians(m_pitch)),
         sin(radians(m_pitch)),
         sin(radians(m_yaw)) * cos(radians(m_pitch))
      );
      m_front = normalize(front);
      m_right = Vector3(
         rotate(radians(m_roll), m_front) *
         Vector4(normalize(cross(m_front, m_worldUp)))
      );
      m_up = Vector3(
         rotate(radians(m_roll), m_front) *
         Vector4(normalize(cross(m_right, m_front)))
      );
   }
}