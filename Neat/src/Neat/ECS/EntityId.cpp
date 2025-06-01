#include "Neat/ECS/EntityId.hpp"

namespace Neat {
std::ostream &operator<<(std::ostream &os, const EntityId &id) {
  os << "Entity::Id(" << id.index() << "." << id.version() << ")";
  return os;
}
}  // namespace Neat