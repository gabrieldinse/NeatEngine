#include "NeatPCH.hpp"

#include "Physics2DUtils.hpp"

namespace Neat {
namespace Physics2DUtils {
b2BodyType toB2BodyType(RigidBody2DType type) {
  switch (type) {
    case RigidBody2DType::Static:
      return b2_staticBody;
    case RigidBody2DType::Dynamic:
      return b2_dynamicBody;
    case RigidBody2DType::Kinematic:
      return b2_kinematicBody;
    default:
      NT_CORE_ASSERT(false, "Unknown RigidBody2DType");
      return b2_staticBody;
  }
}
}  // namespace Physics2DUtils
}  // namespace Neat
