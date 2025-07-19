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
  OrthographicCamera(const Vector2F &position, float size,
                     KeepAspect keepAspect = KeepAspect::Height);

  void setAspectRatio(float aspectRatio, KeepAspect keepAspect);
  void setAspectRatio(float aspectRatio);
  void setZoomLevel(float zoomLevel);
  void setPosition(const Vector2F &position);

  const Vector3F &getPosition() const { return m_position; }
  float getRotation() const { return m_rotation; }

  void incrementRotation(float rotation);
  void setRotation(float rotation);

  void incrementPosition(const Vector2F &position);
  void moveUp(float distance);
  void moveDown(float distance);
  void moveRight(float distance);
  void moveLeft(float distance);

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