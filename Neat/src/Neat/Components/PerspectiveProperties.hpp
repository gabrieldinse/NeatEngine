#pragma once

#include <type_traits>

namespace Neat {
struct PerspectiveProperties {
  float fov = 45.0f;
  float aspectRatio = 16.0f / 9.0f;
  float near = 0.1f;
  float far = 1000.0f;

  void setProperties(float fov, float aspectRatio, float near, float far) {
    fov = fov;
    aspectRatio = aspectRatio;
    near = near;
    far = far;
  }

  void setAspectRatio(float aspect) { aspectRatio = aspect; }

  template <typename T, typename U>
    requires std::is_integral_v<T> and std::is_integral_v<U>
  void setAspectRatio(T width, U height) {
    if (height == 0) {
      return;
    }

    setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
  }
};
}  // namespace Neat