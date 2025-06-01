#include "Neat/ECS/EntityManager.hpp"

namespace Neat {
EntityManager::EntityManager(EventManager &eventManager)
    : m_eventManager(eventManager) {}

EntityManager::~EntityManager() { reset(); }

void EntityManager::reset() {
  for (Entity entity : entitiesForDebugging()) entity.destroy();

  for (BaseMemoryPool *pool : m_componentArrays)
    if (pool != nullptr) delete pool;

  m_componentArrays.clear();
  m_entityComponentMasks.clear();
  m_entityIdsVersion.clear();
  m_freeEntityIds.clear();
  m_indexCounter = 0;
}
}  // namespace Neat