#include <cmath>

#include "Neat/Core/Log.h"
#include "Neat/Graphics/Camera.h"
#include "Neat/Math/MatrixTransform.h"
#include "Neat/Math/Projection.h"
#include "Neat/Math/MatrixOperations.h"
#include "Neat/Math/Utility.h"


namespace Neat
{
   Camera::Camera(const Vector3& position, const Vector3& upDirection, float pitch,
      float yaw, float roll)
      : m_cameraType(CameraType::None)
      , m_position(position)
      , m_worldUpDirection(normalize(upDirection))
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
         left, right, bottom, top);
      m_near = near;
      m_far = far;
      m_cameraType = CameraType::Orthographic;

      return *this;
   }

   Camera& Camera::setPerspective(float fov, float aspectRatio, float near,
      float far)
   {
      m_cameraData = PerspectiveCameraProperties(fov, aspectRatio);
      m_near = near;
      m_far = far;
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

   void Camera::setPitch(float pitch)
   {
      m_pitch = pitch;
      updateOrientationVectors();
   }

   void Camera::setYaw(float yaw)
   {
      m_yaw = yaw;
      updateOrientationVectors();
   }

   void Camera::setRoll(float roll)
   {
      m_roll = roll;
      updateOrientationVectors();
   }


   void Camera::incrementRotation(float pitch, float yaw, float roll)
   {
      m_pitch += pitch;
      m_yaw += yaw;
      m_roll += roll;
      updateOrientationVectors();
   }

   void Camera::incrementPitch(float pitch)
   {
      m_pitch += pitch;
      updateOrientationVectors();
   }

   void Camera::incrementYaw(float yaw)
   {
      m_yaw += yaw;
      updateOrientationVectors();
   }

   void Camera::incrementRoll(float roll)
   {
      m_roll += roll;
      updateOrientationVectors();
   }


   Matrix4 Camera::getProjectionMatrix() const
   {
      switch (m_cameraType)
      {
         case CameraType::Orthographic:
         {
            auto& camera_data = getOrthographicData();
            return orthographic(camera_data.left, camera_data.right,
                  camera_data.bottom, camera_data.top, m_near, m_far);
         }
         case CameraType::Perspective:
         {
            auto& camera_data = getPerspectiveData();
            return perspective(radians(camera_data.fieldOfView),
               camera_data.aspectRatio, m_near, m_far);
         }
      }

      throw CameraTypeHasNotBeenSettedError();
   }

   Matrix4 Camera::getViewMatrix() const
   {
      return lookAtRH(m_position, m_position + m_frontDirection, m_upDirection);
   }

   Matrix4 Camera::getCameraTransform() const
   {
      return getProjectionMatrix() * getViewMatrix();
   }


   // Perspective
   float Camera::getFieldOfView() const
   {
      checkIsPerspective();
      
      return getPerspectiveData().fieldOfView;
   }

   float Camera::getAspectRatio() const
   {
      checkIsPerspective();

      return getPerspectiveData().aspectRatio;
   }

   void Camera::setFieldOfView(float fieldOfView)
   {
      checkIsPerspective();

      getPerspectiveData().fieldOfView = fieldOfView;
   }

   void Camera::setAspectRatio(float aspectRatio)
   {
      checkIsPerspective();
      
      getPerspectiveData().aspectRatio = aspectRatio;
   }


   // Orthographic
   float Camera::getLeft() const
   {
      checkIsOrthographic();

      return getOrthographicData().left;
   }

   float Camera::getRight() const
   {
      checkIsOrthographic();

      return getOrthographicData().right;
   }

   float Camera::getBottom() const
   {
      checkIsOrthographic();

      return getOrthographicData().bottom;
   }

   float Camera::getTop() const
   {
      checkIsOrthographic();

      return getOrthographicData().top;
   }

   void Camera::setLeft(float left)
   {
      checkIsOrthographic();
      
      getOrthographicData().left = left;
   }

   void Camera::setRight(float right)
   {
      checkIsOrthographic();

      getOrthographicData().right = right;
   }

   void Camera::setBottom(float bottom)
   {
      checkIsOrthographic();

      getOrthographicData().bottom = bottom;
   }

   void Camera::setTop(float top)
   {
      checkIsOrthographic();
      
      getOrthographicData().top = top;
   }


   void Camera::updateOrientationVectors()
   {
      m_frontDirection = normalize(Vector3(
         std::cos(radians(m_yaw)) * std::cos(radians(m_pitch)),
         std::sin(radians(m_pitch)),
         std::sin(radians(m_yaw)) * std::cos(radians(m_pitch))
      ));
      m_rightDirection = Vector3(
         rotate(radians(m_roll), m_frontDirection) *
         Vector4(normalize(cross(m_frontDirection, m_worldUpDirection)), 1.0f)
      );
      m_upDirection = Vector3(
         rotate(radians(m_roll), m_frontDirection) *
         Vector4(normalize(cross(m_rightDirection, m_frontDirection)), 1.0f)
      );
   }
}