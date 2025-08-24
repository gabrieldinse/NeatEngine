#pragma once

#include "Neat/Math/Vector.hpp"
#include "Neat/Math/Quaternion.hpp"
#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Transform.hpp"

namespace Neat {
struct TransformComponent {
  Vector3F position{0.0f, 0.0f, 0.0f};
  Vector3F scaling{1.0f, 1.0f, 1.0f};
  Vector3F rotation{0.0f, 0.0f, 0.0f};

  TransformComponent() = default;
  TransformComponent(const Vector3F &position,
                     const Vector3F &scaling = {1.0f, 1.0f, 1.0f},
                     const Vector3F &rotation = {0.0f, 0.0f, 0.0f})
      : position(position), scaling(scaling), rotation(rotation) {}
  TransformComponent(const Vector2F &position,
                     const Vector2F &scaling = {1.0f, 1.0f},
                     float rotation = 0.0f)
      : position(Vector3F{position, 0.0f}),
        scaling(Vector3F{scaling, 1.0f}),
        rotation(Vector3F{0.0f, 0.0f, rotation}) {}
  TransformComponent(const Vector3F &position,
                     const Vector2F &scaling = {1.0f, 1.0f},
                     float rotation = 0.0f)
      : position(position),
        scaling(Vector3F{scaling, 1.0f}),
        rotation(Vector3F{0.0f, 0.0f, rotation}) {}

  Vector2F getPosition2D() const { return Vector2F{position.x, position.y}; }
  float getRotationX() const { return rotation.x; }
  float getRotationY() const { return rotation.y; }
  float getRotationZ() const { return rotation.z; }

  void setPosition(const Vector3F &newPosition) { position = newPosition; }
  void setPosition(float x, float y, float z) { setPosition({x, y, z}); }
  void setPosition(const Vector2F &newPosition) {
    position = Vector3F{newPosition, position.z};
  }
  void setPosition(float x, float y) { setPosition({x, y}); }

  void incrementPosition(const Vector3F &offset) { position += offset; }
  void incrementPosition(float x, float y, float z) {
    incrementPosition({x, y, z});
  }
  void incrementPosition(const Vector2F &offset) {
    position.x += offset.x;
    position.y += offset.y;
  }
  void incrementPosition(float x, float y) { incrementPosition({x, y}); }

  void setX(float x) { position.x = x; }
  void setY(float y) { position.y = y; }
  void setZ(float z) { position.z = z; }
  void incrementX(float offset) { position.x += offset; }
  void incrementY(float offset) { position.y += offset; }
  void incrementZ(float offset) { position.z += offset; }

  void setRotation(const Vector3F &rotation) { this->rotation = rotation; }
  void incrementRotation(const Vector3F &rotationIncrement) {
    rotation += rotationIncrement;
  }

  void setRotationX(float angleDegrees) { rotation.x = angleDegrees; }
  void setRotationXRadians(float angleRadians) {
    rotation.x = radiansToDegrees(angleRadians);
  }
  void incrementRotationX(float angleDegrees) { rotation.x += angleDegrees; }
  void incrementRotationXRadians(float angleRadians) {
    rotation.x += radiansToDegrees(angleRadians);
  }

  void setRotationY(float angleDegrees) { rotation.y = angleDegrees; }
  void setRotationYRadians(float angleRadians) {
    rotation.y = radiansToDegrees(angleRadians);
  }
  void incrementRotationY(float angleDegrees) { rotation.y += angleDegrees; }
  void incrementRotationYRadians(float angleRadians) {
    rotation.y += radiansToDegrees(angleRadians);
  }

  void setRotationZ(float angleDegrees) { rotation.z = angleDegrees; }
  void setRotationZRadians(float angleRadians) {
    rotation.z = radiansToDegrees(angleRadians);
  }
  void incrementRotationZ(float angleDegrees) { rotation.z += angleDegrees; }
  void incrementRotationZRadians(float angleRadians) {
    rotation.z += radiansToDegrees(angleRadians);
  }
  void setRotation(float angleDegrees) { setRotationZ(angleDegrees); }
  void setRotationRadians(float angleRadians) {
    setRotationZRadians(angleRadians);
  }
  void incrementRotation(float angleDegrees) {
    incrementRotationZ(angleDegrees);
  }
  void incrementRotationRadians(float angleRadians) {
    incrementRotationZRadians(angleRadians);
  }

  Matrix4F getTransform() const {
    Matrix4F rotationTransform =
        QuaternionF::fromEulerAngles(degreesToRadians(rotation)).toMatrix4();
    return translate(position) * rotationTransform * scale(scaling);
  }
};
}  // namespace Neat