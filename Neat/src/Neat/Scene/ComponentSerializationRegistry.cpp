#include "NeatPCH.hpp"

#include "Reflectors.hpp"
#include "ComponentSerializationRegistry.hpp"

namespace Neat {
ComponentSerializationRegistry::ComponentSerializationRegistry() {
  registerComponent<TransformComponent>("TransformComponent");
  registerComponent<LabelComponent>("LabelComponent");
}
}  // namespace Neat