#pragma once

#include <variant>
#include <type_traits>

#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Projection.hpp"

namespace Neat {
enum class CameraType { Orthographic = 0, Perspective = 1 };

struct OrthographicProperties {
  float left = -1.0f;
  float right = 1.0f;
  float bottom = -1.0f;
  float top = 1.0f;
  float near = -1.0f;
  float far = 1.0f;

  OrthographicProperties() = default;

  OrthographicProperties(float aspectRatio, float zoomLevel = 1.0f) {
    setProperties(aspectRatio, zoomLevel);
  }

  template <typename T, typename U>
    requires std::is_integral_v<T> and std::is_integral_v<U>
  OrthographicProperties(T width, U height, float zoomLevel = 1.0f) {
    setProperties(width, height, zoomLevel);
  }

  OrthographicProperties(float left, float right, float bottom, float top,
                         float near = -1.0f, float far = 1.0f) {
    setProperties(left, right, bottom, top, near, far);
  }

  void setProperties(float aspectRatio, float zoomLevel = 1.0f) {
    left = -aspectRatio * zoomLevel;
    right = aspectRatio * zoomLevel;
    bottom = -zoomLevel;
    top = zoomLevel;
  }

  template <typename T, typename U>
    requires std::is_integral_v<T> and std::is_integral_v<U>
  void setProperties(T width, U height, float zoomLevel = 1.0f) {
    setProperties(static_cast<float>(width) / static_cast<float>(height),
                  zoomLevel);
  }

  void setProperties(float left, float right, float bottom, float top,
                     float near = -1.0f, float far = 1.0f) {
    left = left;
    right = right;
    bottom = bottom;
    top = top;
    near = near;
    far = far;
  }

  float getAspectRatio() const { return right / top; }

  void setAspectRatio(float aspectRatio) {
    float zoomLevel = top;
    left = -aspectRatio * zoomLevel;
    right = aspectRatio * zoomLevel;
  }

  template <typename T, typename U>
    requires std::is_integral_v<T> and std::is_integral_v<U>
  void setAspectRatio(T width, U height) {
    setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
  }

  float getZoomLevel() const { return top; }

  void setZoomLevel(float zoomLevel) {
    float aspectRatio = right / top;
    bottom = -zoomLevel;
    top = zoomLevel;
    left = -aspectRatio * zoomLevel;
    right = aspectRatio * zoomLevel;
  }
};

struct PerspectiveProperties {
  float fov = 45.0f;
  float aspectRatio = 16.0f / 9.0f;
  float near = 0.1f;
  float far = 100.0f;

  PerspectiveProperties() = default;

  void setProperties(float fov, float aspectRatio, float near, float far) {
    fov = fov;
    aspectRatio = aspectRatio;
    near = near;
    far = far;
  }
};

class CameraComponent {
 public:
  CameraComponent() = delete;
  CameraComponent(const OrthographicProperties &orthographicProperties);
  CameraComponent(const PerspectiveProperties &perspectiveProperties);

  const Matrix4F &getProjection() const { return m_projectionMatrix; }

  CameraType getType() const { return m_type; }
  void setType(CameraType type) { m_type = type; }

  void setOrthographic(const OrthographicProperties &orthographicProperties);
  void setPerspective(const PerspectiveProperties &perspectiveProperties);

  void setOrthographicLeft(float left);
  void setOrthographicRight(float right);
  void setOrthographicBottom(float bottom);
  void setOrthographicTop(float top);
  void setOrthographicNear(float near);
  void setOrthographicFar(float far);
  void setOrthographicAspectRatio(float aspectRatio);
  template <typename T, typename U>
    requires std::is_integral_v<T> and std::is_integral_v<U>
  void setOrthographicAspectRatio(T width, U height) {
    m_orthographicProperties.setAspectRatio(width, height);
    updateProjection();
  }
  void setOrthographicZoomLevel(float zoomLevel);
  float getOrthographicLeft() const { return m_orthographicProperties.left; }
  float getOrthographicRight() const { return m_orthographicProperties.right; }
  float getOrthographicBottom() const {
    return m_orthographicProperties.bottom;
  }
  float getOrthographicTop() const { return m_orthographicProperties.top; }
  float getOrthographicNear() const { return m_orthographicProperties.near; }
  float getOrthographicFar() const { return m_orthographicProperties.far; }
  float getOrthographicZoomLevel() const {
    return m_orthographicProperties.getZoomLevel();
  }
  float getOrthographicAspectRatio() const {
    return m_orthographicProperties.getAspectRatio();
  }

  void setPerspectiveFOV(float fov);
  void setPerspectiveAspectRatio(float aspectRatio);
  void setPerspectiveNear(float near);
  void setPerspectiveFar(float far);
  float getPerspectiveFOV() const { return m_perspectiveProperties.fov; }
  float getPerspectiveAspectRatio() const {
    return m_perspectiveProperties.aspectRatio;
  }
  float getPerspectiveNear() const { return m_perspectiveProperties.near; }
  float getPerspectiveFar() const { return m_perspectiveProperties.far; }

 private:
  void updateProjection();

 private:
  CameraType m_type;
  OrthographicProperties m_orthographicProperties;
  PerspectiveProperties m_perspectiveProperties;
  Matrix4F m_projectionMatrix{1.0f};
};
}  // namespace Neat