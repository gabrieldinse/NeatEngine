#pragma once

#include <type_traits>

#include "Core/Log.hpp"

namespace Neat {
struct OrthographicProperties {
  float left = -1.0f;
  float right = 1.0f;
  float bottom = -1.0f;
  float top = 1.0f;
  float near = -1.0f;
  float far = 1.0f;

  OrthographicProperties() = default;

  OrthographicProperties(float aspectRatio, float size = 2.0f) {
    setProperties(aspectRatio, size);
  }

  template <typename T, typename U>
    requires std::is_integral_v<T> and std::is_integral_v<U>
  OrthographicProperties(T width, U height, float size = 2.0f) {
    setProperties(width, height, size);
  }

  OrthographicProperties(float left, float right, float bottom, float top,
                         float near = -1.0f, float far = 1.0f) {
    setProperties(left, right, bottom, top, near, far);
  }

  void setProperties(float aspectRatio, float size = 2.0f) {
    float halfSize = size * 0.5f;
    left = -aspectRatio * halfSize;
    right = aspectRatio * halfSize;
    bottom = -halfSize;
    top = halfSize;
  }

  template <typename T, typename U>
    requires std::is_integral_v<T> and std::is_integral_v<U>
  void setProperties(T width, U height, float size = 2.0f) {
    if (height == 0) {
      NT_CORE_WARN("Tried to set orthographic properties with height 0.");
      return;
    }

    setProperties(static_cast<float>(width) / static_cast<float>(height), size);
  }

  void setProperties(float leftVal, float rightVal, float bottomVal, float topVal,
                     float nearVal = -1.0f, float farVal = 1.0f) {
    left = leftVal;
    right = rightVal;
    bottom = bottomVal;
    top = topVal;
    near = nearVal;
    far = farVal;
  }

  float getAspectRatio() const { return (right - left) / (top - bottom); }

  void setAspectRatio(float aspectRatio) {
    float halfSize = getSize() * 0.5f;
    left = -aspectRatio * halfSize;
    right = aspectRatio * halfSize;
  }

  template <typename T, typename U>
    requires std::is_integral_v<T> and std::is_integral_v<U>
  void setAspectRatio(T width, U height) {
    if (height == 0) {
      NT_CORE_WARN("Tried to set orthographic aspect ratio with height 0.");
      return;
    }

    setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
  }

  float getSize() const { return top - bottom; }

  void setSize(float size) {
    float aspectRatio = getAspectRatio();
    float halfSize = size * 0.5f;
    bottom = -halfSize;
    top = halfSize;
    left = -aspectRatio * halfSize;
    right = aspectRatio * halfSize;
  }
};
}  // namespace Neat