#pragma once

#include "Neat/Math/Vector.hpp"
#include "Neat/Math/Quaternion.hpp"
#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Transform.hpp"

namespace Neat {
struct TransformComponent {
  Vector3F position{0.0f, 0.0f, 0.0f};
  Vector3F rotation{0.0f, 0.0f, 0.0f};
  Vector3F scale{1.0f, 1.0f, 1.0f};

  TransformComponent() = default;
  TransformComponent(const Vector3F &position,
                     const Vector3F &rotation = {0.0f, 0.0f, 0.0f},
                     const Vector3F &scale = {1.0f, 1.0f, 1.0f})
      : position(position), rotation(rotation), scale(scale) {}

  Matrix4F getTransform() const {
    Matrix4F rotation =
        QuaternionF::fromEulerAngles(this->rotation).toMatrix4();
    Matrix4F translation = translate(position);
    Matrix4F scaling = Neat::scale(scale);
    return translation * rotation * scaling;
  }
};
}  // namespace Neat