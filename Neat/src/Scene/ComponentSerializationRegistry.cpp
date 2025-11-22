#include "NeatPCH.hpp"

#include "Reflectors.hpp"
#include "ComponentSerializationRegistry.hpp"

#include "Components/ActiveCameraTagComponent.hpp"
#include "Components/BoxCollider2DComponent.hpp"
#include "Components/CameraComponent.hpp"
#include "Components/LabelComponent.hpp"
#include "Components/RenderableSpriteComponent.hpp"
#include "Components/RigidBody2DComponent.hpp"
#include "Components/TransformComponent.hpp"

namespace Neat {
ComponentSerializationRegistry::ComponentSerializationRegistry() {
  NT_PROFILE_FUNCTION();

  registerComponent<ActiveCameraTagComponent>("ActiveCameraTagComponent");
  registerComponent<BoxCollider2DComponent>("BoxCollider2DComponent");
  registerComponent<CameraComponent>("CameraComponent");
  registerComponent<LabelComponent>("LabelComponent");
  registerComponent<RenderableSpriteComponent>("RenderableSpriteComponent");
  registerComponent<RigidBody2DComponent>("RigidBody2DComponent");
  registerComponent<TransformComponent>("TransformComponent");
}
}  // namespace Neat