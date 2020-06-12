#pragma once

#include <variant>

#include "Neat/Math/Matrix.h"
#include "Neat/Math/Vector.h"
#include "Neat/Math/Projection.h"

#undef near
#undef far


namespace Neat
{
   class Camera
   {
   public:
      enum class CameraType : UInt16
      {
         None,
         Orthographic,
         Perspective
      };

      struct OrthographicCameraProperties
      {
         OrthographicCameraProperties(float left = 0.0f, float right = 0.0f,
            float bottom = 0.0f, float top = 0.0f, float near = 0.0f,
            float far = 0.0f)
            : left(left), right(right), bottom(bottom), top(top), near(near)
            , far(far) {}

         float left;
         float right;
         float bottom;
         float top;
         float near;
         float far;
      };

      struct PerspectiveCameraProperties
      {
         PerspectiveCameraProperties(float fieldOfView = 0.0f,
            float aspectRatio = 0.0f, float near = 0.0f, float far = 0.0f)
          : fieldOfView(fieldOfView), aspectRatio(aspectRatio), near(near)
          , far(far) {}

         float fieldOfView;
         float aspectRatio;
         float near;
         float far;
      };

      using CameraData =
         std::variant<
         OrthographicCameraProperties,
         PerspectiveCameraProperties
         >;

   public:
      Camera(const Vector3& position = { 0.0f, 0.0f, 15.0f },
         const Vector3& up = { 0.0f, 1.0f, 0.0f }, float pitch = 0.0f,
         float yaw = -90.0f, float roll = 0.0f);

      Camera& setOrthographic(float left, float right, float bottom, float top,
         float near = -100.0f, float far = 100.0f);
      Camera& setPerspective(float fov = 45.0f,
         float aspectRatio = 16.0f / 9.0f, float near = 0.1f,
         float far = 1000.f);

      void updateOrientationVectors();

      const Vector3& getPosition() const { return m_position; }
      float getYaw() const { return m_yaw; }
      float getPitch() const { return m_pitch; }
      float getRoll() const { return m_roll; }
      const Vector3& getFront() const { return m_front; }
      const Vector3& getUp() const { return m_up; }
      const Vector3& getRight() const { return m_right; }
      
      CameraType getCameraType() const { return m_cameraType; }

      void setPosition(const Vector3& position) { m_position = position; }
      void setRotation(float pitch, float yaw, float roll);
      void setYaw(float yaw);
      void setPitch(float pitch);
      void setRoll(float roll);
      void setWorldUp(const Vector3& worldUp) { m_worldUp = worldUp; }

      Matrix4 getProjectionMatrix() const;
      Matrix4 getViewMatrix() const;
      Matrix4 getCameraTransform() const;

   private:
      const OrthographicCameraProperties& getOrthographicData() const
      {
         return std::get<OrthographicCameraProperties>(m_cameraData);
      }

      OrthographicCameraProperties& getOrthographicData()
      {
         return std::get<OrthographicCameraProperties>(m_cameraData);
      }

      const PerspectiveCameraProperties& getPerspectiveData() const
      {
         return std::get<PerspectiveCameraProperties>(m_cameraData);
      }

      PerspectiveCameraProperties& getPerspectiveData()
      {
         return std::get<PerspectiveCameraProperties>(m_cameraData);
      }

   private:
      CameraType m_cameraType;
      CameraData m_cameraData;
      Vector3 m_worldUp;
      Vector3 m_position;
      Vector3 m_front{ 0.0f };
      Vector3 m_right{ 0.0f };
      Vector3 m_up{ 0.0f };
      float m_yaw;
      float m_pitch;
      float m_roll;
   };
}