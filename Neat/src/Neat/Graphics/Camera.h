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
      enum class CameraType
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
            : left(left), right(right), bottom(bottom), top(top) {}

         float left;
         float right;
         float bottom;
         float top;
      };


      struct PerspectiveCameraProperties
      {
         PerspectiveCameraProperties(float fieldOfView = 0.0f,
            float aspectRatio = 0.0f, float near = 0.0f, float far = 0.0f)
          : fieldOfView(fieldOfView), aspectRatio(aspectRatio) {}

         float fieldOfView;
         float aspectRatio;
      };

      using CameraData =
         std::variant<
         OrthographicCameraProperties,
         PerspectiveCameraProperties
         >;

   public:
      Camera(const Vector3& position = { 0.0f, 0.0f, 15.0f },
         const Vector3& upDirection = { 0.0f, 1.0f, 0.0f }, float pitch = 0.0f,
         float yaw = -90.0f, float roll = 0.0f);

      Camera& setOrthographic(float left, float right, float bottom, float top,
         float near = -100.0f, float far = 100.0f);
      Camera& setPerspective(float fov = 45.0f,
         float aspectRatio = 16.0f / 9.0f, float near = 0.1f,
         float far = 1000.f);

      const Vector3& getPosition() const { return m_position; }
      float getPitch() const { return m_pitch; }
      float getYaw() const { return m_yaw; }
      float getRoll() const { return m_roll; }
      const Vector3& getFrontDirection() const { return m_frontDirection; }
      const Vector3& getUpDirection() const { return m_upDirection; }
      const Vector3& getRightDirection() const { return m_rightDirection; }
      float getNear() const { return m_near; }
      float getFar() const { return m_far; }

      void setPosition(const Vector3& position) { m_position = position; }
      void setRotation(float pitch, float yaw, float roll);
      void setPitch(float pitch);
      void setYaw(float yaw);
      void setRoll(float roll);
      void setWorldUp(const Vector3& worldUp) { m_worldUpDirection = worldUp; }

      void incrementPosition(const Vector3& position) { m_position += position; }
      void incrementX(float x) { m_position.x += x; }
      void incrementY(float y) { m_position.y += y; }
      void incrementZ(float z) { m_position.z += z; }
      void incrementRotation(float pitch, float yaw, float roll);
      void incrementPitch(float pitch);
      void incrementYaw(float yaw);
      void incrementRoll(float roll);

      Matrix4 getProjectionMatrix() const;
      Matrix4 getViewMatrix() const;
      Matrix4 getCameraTransform() const;

      bool isOrthographic() const { return m_cameraType == CameraType::Orthographic; }
      bool isPerspective() const { return m_cameraType == CameraType::Perspective; }

      // Perspective
      float getFieldOfView() const;
      float getAspectRatio() const;
      void setFieldOfView(float fieldOfView);
      void setAspectRatio(float aspectRatio);

      // Orthographic
      float getLeft() const;
      float getRight() const;
      float getBottom() const;
      float getTop() const;
      void setLeft(float left);
      void setRight(float right);
      void setBottom(float bottom);
      void setTop(float top);

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


      void checkIsOrthographic() const
      {
         if (m_cameraType == CameraType::Perspective)
            throw WrongCameraTypeError();
         
         if (m_cameraType == CameraType::None)
            throw CameraTypeHasNotBeenSettedError();
      }

      void checkIsPerspective() const
      {
         if (m_cameraType == CameraType::Orthographic)
            throw WrongCameraTypeError();

         if (m_cameraType == CameraType::None)
            throw CameraTypeHasNotBeenSettedError();
      }


      void updateOrientationVectors();

   private:
      CameraType m_cameraType;
      CameraData m_cameraData;
      Vector3 m_position;
      Vector3 m_worldUpDirection;
      Vector3 m_frontDirection{ 0.0f };
      Vector3 m_rightDirection{ 0.0f };
      Vector3 m_upDirection{ 0.0f };
      float m_yaw;
      float m_pitch;
      float m_roll;
      float m_near = 0.0f;
      float m_far = 0.0f;
   };
}