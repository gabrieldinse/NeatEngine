#pragma once

#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Projection.hpp"

namespace Neat {
class CameraComponent {
 public:
  CameraComponent(const Matrix4F &projection);
  CameraComponent() = default;
  CameraComponent(float left, float right, float bottom, float top,
                  float near = -1.0f, float far = 1.0f);
  CameraComponent(float aspectRatio, float zoomLevel = 1.0f);
  CameraComponent(UInt32 width, UInt32 height, float zoomLevel = 1.0f);

  const Matrix4F &getProjection() const { return m_projectionMatrix; }

  static CameraComponent createOrthographic(float left, float right,
                                            float bottom, float top,
                                            float near = -1.0f,
                                            float far = 1.0f);
  static CameraComponent createOrthographic(float aspectRatio,
                                            float zoomLevel = 1.0f);
  static CameraComponent createOrthographic(UInt32 width, UInt32 height,
                                            float zoomLevel = 1.0f);

  void setOrthographic(float left, float right, float bottom, float top,
                       float near = -1.0f, float far = 1.0f);
  void setOrthographic(float aspectRatio, float zoomLevel = 1.0f);
  void setOrthographic(UInt32 width, UInt32 height, float zoomLevel = 1.0f);

 private:
  Matrix4F m_projectionMatrix{1.0f};
};
}  // namespace Neat