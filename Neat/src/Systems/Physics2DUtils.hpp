#pragma once

#include "Components/RigidBody2DComponent.hpp"

#include <box2d/box2d.h>

namespace Neat {
namespace Physics2DUtils {
b2BodyType toB2BodyType(RigidBody2DType type);
}  // namespace Physics2DUtils
}  // namespace Neat
