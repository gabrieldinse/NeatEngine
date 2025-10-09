#pragma once

#include <any>

#include <box2d/box2d.h>

namespace Neat {
enum class RigidBody2DType { Static = 0, Dynamic, Kinematic };

struct RigidBody2DComponent {
  RigidBody2DType type = RigidBody2DType::Static;
  bool fixedRotation = false;
  b2BodyId bodyID;
};
}  // namespace Neat