#pragma once

#include "Neat/Graphics/Cameras/Camera.hpp"
#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Projection.hpp"
#include "Neat/Math/Vector.hpp"
#include "Neat/Math/Quaternion.hpp"

namespace Neat {
enum class KeepAspect { Height, Width };

class OrthographicCamera : public Camera {
 public:
  OrthographicCamera(const Vector2F &position, float aspectRatio,
                     float zoomLevel = 1.0f,
                     KeepAspect keepAspect = KeepAspect::Height);
  OrthographicCamera(const Vector2F &position, UInt32 width, UInt32 height,
                     float zoomLevel = 1.0f,
                     KeepAspect keepAspect = KeepAspect::Height);

  void setProperties(float aspectRatio,
                     KeepAspect keepAspect = KeepAspect::Height,
                     float zoomLevel = 1.0f);
  void setAspectRatio(float aspectRatio, KeepAspect keepAspect);
  void setAspectRatio(float aspectRatio);
  void setZoomLevel(float zoomLevel);
  void setSize(float size) { setZoomLevel(size); }
  void setPosition(const Vector2F &position);

  const Vector3F &getPosition() const { return m_position; }
  float getRotation() const { return m_rotation; }
  float getZoomLevel() const { return m_zoomLevel; }
  float getSize() const { return getZoomLevel(); }
  float getAspectRatio() const { return m_aspectRatio; }

  void incrementRotation(float rotation);
  void setRotation(float rotation);

  void incrementPosition(const Vector2F &position);
  void moveUp(float distance);
  void moveDown(float distance);
  void moveRight(float distance);
  void moveLeft(float distance);

  void setX(float x);
  void setY(float y);
  void incrementX(float x);
  void incrementY(float y);

  virtual const Matrix4F &getProjectionMatrix() const override {
    return m_projectionMatrix;
  }
  virtual const Matrix4F &getViewMatrix() const override {
    return m_viewMatrix;
  }
  virtual const Matrix4F &getCameraTransform() const override {
    return m_cameraTransform;
  }

 private:
  void updateProjection();
  void updateViewMatrix();
  void updateCameraTransform();

 private:
  Vector3F m_position;
  float m_aspectRatio;
  KeepAspect m_keepAspect = KeepAspect::Height;
  Matrix4F m_viewMatrix{Matrix4F::identity()};
  Matrix4F m_projectionMatrix{Matrix4F::identity()};
  Matrix4F m_cameraTransform{Matrix4F::identity()};
  float m_zPos = 0.0f;  // TODO: check this value
  float m_zoomLevel = 1.0f;
  float m_rotation = 0.0f;
};
}  // namespace Neat