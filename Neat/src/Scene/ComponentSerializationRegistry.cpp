#include "NeatPCH.hpp"

#include "Reflectors.hpp"
#include "ComponentSerializationRegistry.hpp"

namespace Neat {
ComponentSerializationRegistry::ComponentSerializationRegistry() {
  NT_PROFILE_FUNCTION();

  registerComponent<LabelComponent>("LabelComponent");
  registerComponent<TransformComponent>("TransformComponent");
  registerComponent<RenderableSpriteComponent>("RenderableSpriteComponent");
  registerComponent<ActiveCameraTagComponent>("ActiveCameraTagComponent");
  registerComponent<CameraComponent>("CameraComponent");
}
}  // namespace Neat