#pragma once

#include <type_traits>

namespace Neat {
struct PerspectiveProperties {
  float fov = 45.0f;
  float aspectRatio = 16.0f / 9.0f;
  float near = 0.1f;
  float far = 100.0f;

  void setProperties(float fov, float aspectRatio, float near, float far) {
    fov = fov;
    aspectRatio = aspectRatio;
    near = near;
    far = far;
  }
};
}  // namespace Neat