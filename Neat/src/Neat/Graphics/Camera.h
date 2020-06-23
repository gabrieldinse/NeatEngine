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
      Camera(const Vector3F& position = { 0.0f, 0.0f, 15.0f },
         const Vector3F& upDirection = { 0.0f, 1.0f, 0.0f }, float pitch = 0.0f,
         float yaw = 0.0f, float roll = 0.0f);

      Camera& setOrthographic(float left, float right, float bottom, float top,
         float near = -100.0f, float far = 100.0f);
      Camera& setPerspective(float fov = 45.0f,
         float aspectRatio = 16.0f / 9.0f, float near = 0.1f,
         float far = 1000.f);

      const Vector3F& getPosition() const { return m_position; }
      float getPitch() const { return m_pitch; }
      float getYaw() const { return m_yaw; }
      float getRoll() const { return m_roll; }
      const Vector3F& getForwardDirection() const { return m_forwardDirection; }
      const Vector3F& getUpDirection() const { return m_upDirection; }
      const Vector3F& getRightDirection() const { return m_rightDirection; }
      float getNear() const { return m_near; }
      float getFar() const { return m_far; }

      void setPosition(const Vector3F& position) { m_position = position; }
      void setX(float x) { m_position.x = x; }
      void setY(float y) { m_position.y = y; }
      void setZ(float z) { m_position.z = z; }
      void setRotation(float pitch, float yaw, float roll);
      void setPitch(float pitch);
      void setYaw(float yaw);
      void setRoll(float roll);
      void setWorldUp(const Vector3F& worldUp) { m_worldUpDirection = worldUp; }

      void rotate(float pitch, float yaw, float roll);
      void rotatePitch(float pitch);
      void rotateYaw(float yaw);
      void rotateRoll(float roll);

      void move(const Vector3F& position) { m_position += position; }
      void moveX(float distance) { m_position.x += distance; }
      void moveY(float distance) { m_position.y += distance; }
      void moveZ(float distance) { m_position.z += distance; }
      void moveUp(float distance) { m_position += m_upDirection * distance; }
      void moveDown(float distance) { m_position -= m_upDirection * distance; }
      void moveRight(float distance) { m_position += m_rightDirection * distance; }
      void moveLeft(float distance) { m_position -= m_rightDirection * distance; }
      void moveForward(float distance) { m_position += m_forwardDirection * distance; }
      void moveBackward(float distance) { m_position -= m_forwardDirection * distance; }

      Matrix4F getProjectionMatrix() const;
      Matrix4F getViewMatrix() const;
      Matrix4F getCameraTransform() const;

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


      void checkIsType(CameraType type) const
      {
         if (m_cameraType == CameraType::None)
            throw CameraTypeHasNotBeenSettedError();

         if (m_cameraType != type)
            throw WrongCameraTypeError();
      }


      void updateOrientationVectors();

   private:
      CameraType m_cameraType;
      CameraData m_cameraData;
      Vector3F m_position;
      Vector3F m_worldUpDirection;
      Vector3F m_forwardDirection{ 0.0f };
      Vector3F m_rightDirection{ 0.0f };
      Vector3F m_upDirection{ 0.0f };
      float m_yaw;
      float m_pitch;
      float m_roll;
      float m_near = 0.0f;
      float m_far = 0.0f;
   };
}