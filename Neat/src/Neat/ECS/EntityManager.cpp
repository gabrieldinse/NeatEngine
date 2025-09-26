#include "NeatPCH.hpp"

#include "EntityManager.hpp"

#include "Neat/Core/Exceptions.hpp"

namespace Neat {
const Entity::ID Entity::InvalidID{ID::InvalidIndex, ID::InvalidVersion};

EntityManager::EntityManager(const Ref<EventDispatcher> &eventDispatcher)
    : m_eventDispatcher(eventDispatcher) {}

EntityManager::~EntityManager() { reset(); }

void EntityManager::reset() {
  for (Entity entity : entities()) {
    entity.destroy();
  }

  for (BaseMemoryPool *pool : m_componentArrays) {
    if (pool != nullptr) {
      delete pool;
    }
  }

  m_componentArrays.clear();
  m_entityComponentMasks.clear();
  m_entityIdsVersion.clear();
  m_freeEntityIds.clear();
  m_indexCounter = 0;
}

bool EntityManager::hasAnyComponent(const Entity::ID &id) const {
  checkIsValid(id);

  return m_entityComponentMasks[id.index()].any();
}

bool Entity::hasAnyComponent() const {
  checkIsValid();

  return m_entityManager->hasAnyComponent(m_id);
}

std::ostream &operator<<(std::ostream &os, const Entity &entity) {
  os << "Entity(" << entity.id() << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const Entity::ID &id) {
  os << "Entity::ID(" << id.version() << "." << id.index() << ")";
  return os;
}
}  // namespace Neat