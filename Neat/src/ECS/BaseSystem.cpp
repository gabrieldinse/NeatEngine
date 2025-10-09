#include "NeatPCH.hpp"

#include "BaseSystem.hpp"

namespace Neat {
BaseSystem::Family BaseSystem::s_familyCounter = 0;

void BaseSystem::onInitialize(const Ref<EntityManager> &entityManager,
                              const Ref<EventDispatcher> &eventDispatcher,
                              LayerID layerID) {
  if (not m_initialized) {
    m_initialized = true;
    initialize(entityManager, eventDispatcher, layerID);
  }
}

void BaseSystem::onUpdate(const Ref<EntityManager> &entityManager,
                          const Ref<EventDispatcher> &eventDispatcher,
                          double deltaTimeSeconds, LayerID layerID) {
  if (not m_initialized) {
    onInitialize(entityManager, eventDispatcher, layerID);
  }

  update(entityManager, eventDispatcher, deltaTimeSeconds, layerID);
}

void BaseSystem::onShutdown(const Ref<EntityManager> &entityManager,
                            const Ref<EventDispatcher> &eventDispatcher,
                            LayerID layerID) {
  if (m_initialized) {
    m_initialized = false;
    shutdown(entityManager, eventDispatcher, layerID);
  }
}
}  // namespace Neat