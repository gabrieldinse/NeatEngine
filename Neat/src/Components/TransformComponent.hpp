#pragma once

#include "Math/Vector.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Matrix.hpp"
#include "Math/Transform.hpp"

namespace Neat {
struct TransformComponent {
  Vector3F position{0.0f, 0.0f, 0.0f};
  Vector3F scaling{1.0f, 1.0f, 1.0f};
  Vector3F rotation{0.0f, 0.0f, 0.0f};

  TransformComponent() = default;
  TransformComponent(const Vector3F &position,
                     const Vector3F &scaling = {1.0f, 1.0f, 1.0f},
                     const Vector3F &rotation = {0.0f, 0.0f, 0.0f})
      : position{position}, scaling{scaling}, rotation{rotation} {}
  TransformComponent(const Vector2F &position,
                     const Vector2F &scaling = {1.0f, 1.0f},
                     float rotation = 0.0f)
      : position{position, 0.0f},
        scaling{scaling, 1.0f},
        rotation{0.0f, 0.0f, rotation} {}
  TransformComponent(const Vector3F &position,
                     const Vector2F &scaling = {1.0f, 1.0f},
                     float rotation = 0.0f)
      : position{position},
        scaling{scaling, 1.0f},
        rotation{0.0f, 0.0f, rotation} {}

  Matrix4F getTransform() const {
    return translate(position) * getOrientation().toMatrix4() * scale(scaling);
  }

  QuaternionF getOrientation() const {
    return QuaternionF::fromEulerAngles(degreesToRadians(rotation));
  }

  Vector2F getPosition2D() const {
    return Vector2F{position.x(), position.y()};
  }
  float getRotationX() const { return rotation.x(); }
  float getRotationY() const { return rotation.y(); }
  float getRotationZ() const { return rotation.z(); }
  float getPitch() const { return getRotationX(); }
  float getYaw() const { return getRotationY(); }
  float getRoll() const { return getRotationZ(); }

  void setPosition(const Vector3F &newPosition) { position = newPosition; }
  void setPosition(float x, float y, float z) { setPosition({x, y, z}); }
  void setPosition(const Vector2F &newPosition) {
    position = Vector3F{newPosition, position.z()};
  }
  void setPosition(float x, float y) { setPosition({x, y}); }

  void incrementPosition(const Vector3F &offset) { position += offset; }
  void incrementPosition(float x, float y, float z) {
    incrementPosition({x, y, z});
  }
  void incrementPosition(const Vector2F &offset) {
    position += Vector3F{offset};
  }
  void incrementPosition(float x, float y) { incrementPosition({x, y}); }

  void setX(float x) { position.x() = x; }
  void setY(float y) { position.y() = y; }
  void setZ(float z) { position.z() = z; }
  void incrementX(float offset) { position.x() += offset; }
  void incrementY(float offset) { position.y() += offset; }
  void incrementZ(float offset) { position.z() += offset; }

  void setRotation(const Vector3F &rotationVal) {
    this->rotation = rotationVal;
  }
  void incrementRotation(const Vector3F &rotationIncrement) {
    rotation += rotationIncrement;
  }

  void setRotationX(float angleDegrees) { rotation.x() = angleDegrees; }
  void setRotationXRadians(float angleRadians) {
    rotation.x() = radiansToDegrees(angleRadians);
  }
  void setPitch(float angleDegrees) { setRotationX(angleDegrees); }
  void incrementRotationX(float angleDegrees) { rotation.x() += angleDegrees; }
  void incrementRotationXRadians(float angleRadians) {
    rotation.x() += radiansToDegrees(angleRadians);
  }
  void incrementPitch(float angleDegrees) { incrementRotationX(angleDegrees); }

  void setRotationY(float angleDegrees) { rotation.y() = angleDegrees; }
  void setRotationYRadians(float angleRadians) {
    rotation.y() = radiansToDegrees(angleRadians);
  }
  void setYaw(float angleDegrees) { setRotationY(angleDegrees); }
  void incrementRotationY(float angleDegrees) { rotation.y() += angleDegrees; }
  void incrementRotationYRadians(float angleRadians) {
    rotation.y() += radiansToDegrees(angleRadians);
  }
  void incrementYaw(float angleDegrees) { incrementRotationY(angleDegrees); }

  void setRotationZ(float angleDegrees) { rotation.z() = angleDegrees; }
  void setRotationZRadians(float angleRadians) {
    rotation.z() = radiansToDegrees(angleRadians);
  }
  void setRoll(float angleDegrees) { setRotationZ(angleDegrees); }
  void incrementRotationZ(float angleDegrees) { rotation.z() += angleDegrees; }
  void incrementRotationZRadians(float angleRadians) {
    rotation.z() += radiansToDegrees(angleRadians);
  }
  void incrementRoll(float angleDegrees) { incrementRotationZ(angleDegrees); }

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
};
}  // namespace Neat