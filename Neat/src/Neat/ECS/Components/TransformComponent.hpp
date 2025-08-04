#pragma once

#include "Neat/Math/Vector.hpp"
#include "Neat/Math/Quaternion.hpp"
#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Transform.hpp"

namespace Neat {
struct TransformComponent {
  Vector3F position{0.0f, 0.0f, 0.0f};
  Vector3F scale{1.0f, 1.0f, 1.0f};
  Vector3F rotation{0.0f, 0.0f, 0.0f};

  TransformComponent() = default;
  TransformComponent(const Vector3F &position,
                     const Vector3F &scale = {1.0f, 1.0f, 1.0f},
                     const Vector3F &rotation = {0.0f, 0.0f, 0.0f})
      : position(position), scale(scale), rotation(rotation) {}
  TransformComponent(const Vector2F &position,
                     const Vector2F &scale = {1.0f, 1.0f},
                     float rotation = 0.0f)
      : position(Vector3F{position, 0.0f}),
        scale(Vector3F{scale, 1.0f}),
        rotation(Vector3F{0.0f, 0.0f, rotation}) {}
  TransformComponent(const Vector3F &position,
                     const Vector2F &scale = {1.0f, 1.0f},
                     float rotation = 0.0f)
      : position(position),
        scale(Vector3F{scale, 1.0f}),
        rotation(Vector3F{0.0f, 0.0f, rotation}) {}

  void setPosition(const Vector3F &newPosition) { position = newPosition; }

  void setPosition(const Vector2F &newPosition) {
    position = Vector3F{newPosition, position.z};
  }

  void incrementPosition(const Vector3F &offset) { position += offset; }

  void incrementPosition(const Vector2F &offset) {
    position.x += offset.x;
    position.y += offset.y;
  }

  void setX(float x) { position.x = x; }

  void setY(float y) { position.y = y; }

  void setZ(float z) { position.z = z; }

  void incrementX(float offset) { position.x += offset; }

  void incrementY(float offset) { position.y += offset; }

  void incrementZ(float offset) { position.z += offset; }

  Matrix4F getTransform() const {
    Matrix4F rotation =
        QuaternionF::fromEulerAngles(degreesToRadians(this->rotation))
            .toMatrix4();
    Matrix4F translation = translate(position);
    Matrix4F scaling = Neat::scale(scale);
    return translation * rotation * scaling;
  }
};
}  // namespace Neat