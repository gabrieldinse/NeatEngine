#pragma once

#include "Neat/Math/Matrix.hpp"

namespace Neat {
class ICamera {
 public:
  virtual ~ICamera() = default;
  virtual const Matrix4F &getProjectionMatrix() const = 0;
  virtual const Matrix4F &getViewMatrix() const = 0;
  virtual const Matrix4F &getCameraTransform() const = 0;
};
}  // namespace Neat