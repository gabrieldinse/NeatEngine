#pragma once

#include "Neat/Graphics/Cameras/Camera.hpp"
#include "Neat/Core/Log.hpp"


namespace Neat
{
   enum class KeepAspect
   {
      Height, Width
   };


   class Camera2D
   {
   public:
      Camera2D(const Vector2F& position, float size,
         KeepAspect keepAspect = KeepAspect::Height);

      Camera& getCamera() { return m_camera; }
      const Camera& getCamera() const { return m_camera; }

      const Vector2F getPosition() const { return Vector2F(m_camera.getPosition()); }
      float getRotation() const { return m_camera.getRoll(); }
      const Vector2F getUpDirection() const { return Vector2F(m_camera.getUpDirection()); }
      const Vector2F getRightDirection() const { return Vector2F(m_camera.getRightDirection()); }
      float getSize() const { return m_size; }
      float getZoomLevel() const { return m_zoomLevel; }
      float getNear() const { return m_camera.getNear(); }
      float getFar() const { return m_camera.getFar(); }

      void setSize(float size, KeepAspect keepAspect);
      void setSize(float size);
      void setZoomLevel(float zoomLevel);
      void setPosition(const Vector2F& position) { m_camera.setPosition(Vector3F(position, m_zPos)); }
      void setX(float x) { m_camera.setX(x); }
      void setY(float y) { m_camera.setY(y); }
      void setRotation(float rotation) { m_camera.setRoll(rotation); }
      void setNear(float near) { m_camera.setNear(near); }
      void setFar(float far) { m_camera.setFar(far); }

      void rotate(float rotation) { m_camera.rotateRoll(rotation); }

      void move(const Vector2F& position) { m_camera.move(Vector3F(position, m_zPos)); }
      void moveX(float distance) { m_camera.moveX(distance); }
      void moveY(float distance) { m_camera.moveY(distance); }
      void moveUp(float distance) { m_camera.moveUp(distance); }
      void moveDown(float distance) { m_camera.moveDown(distance); }
      void moveRight(float distance) { m_camera.moveRight(distance); }
      void moveLeft(float distance) { m_camera.moveLeft(distance); }

      Matrix4F getProjectionMatrix() const { return m_camera.getProjectionMatrix(); }
      Matrix4F getViewMatrix() const { return m_camera.getViewMatrix(); }
      Matrix4F getCameraTransform() const { return m_camera.getCameraTransform(); }

   private:
      void updateProjection();

   private:
      float m_zPos = 0.0f; // TODO: check this value
      float m_zoomLevel = 1.0f;
      Camera m_camera;
      float m_size;
      KeepAspect m_keepAspect = KeepAspect::Height;
   };
}