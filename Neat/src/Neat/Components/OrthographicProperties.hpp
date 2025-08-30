#pragma once

#include <type_traits>

namespace Neat {
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
}  // namespace Neat