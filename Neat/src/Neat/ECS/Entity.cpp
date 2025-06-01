#include "Neat/ECS/Entity.hpp"
#include "Neat/ECS/EntityManager.hpp"
#include "Neat/Core/Exceptions.hpp"

namespace Neat {
const EntityId Entity::INVALID_ID;

bool Entity::operator==(const Entity &other) const {
  return other.m_entityManager == m_entityManager and other.m_id == m_id;
}

inline bool Entity::isValid() const {
  return m_entityManager != nullptr and m_entityManager->isValid(m_id);
}

inline void Entity::checkIsValid() const {
  if (m_entityManager == nullptr)
    throw InvalidEntityError("Assigned EntityManager is null.");

  m_entityManager->checkIsValid(m_id);
}

inline void Entity::invalidate() {
  m_id = INVALID_ID;
  m_entityManager = nullptr;
}

std::ostream &operator<<(std::ostream &os, const Entity &entity) {
  os << "Entity(" << entity.id() << ")";
  return os;
}
}  // namespace Neat