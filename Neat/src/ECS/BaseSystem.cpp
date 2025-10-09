#include "NeatPCH.hpp"

#include "BaseSystem.hpp"

namespace Neat {
BaseSystem::Family BaseSystem::s_familyCounter = 0;

void BaseSystem::initialize(const Ref<EntityManager> &entityManager,
                            const Ref<EventDispatcher> &eventDispatcher,
                            LayerID layerID) {
  if (not m_initialized) {
    m_initialized = true;
    onInitialize(entityManager, eventDispatcher, layerID);
  }
}

void BaseSystem::update(const Ref<EntityManager> &entityManager,
                        const Ref<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds, LayerID layerID) {
  if (not m_initialized) {
    initialize(entityManager, eventDispatcher, layerID);
  }

  onUpdate(entityManager, eventDispatcher, deltaTimeSeconds, layerID);
}

void BaseSystem::shutdown(const Ref<EntityManager> &entityManager,
                          const Ref<EventDispatcher> &eventDispatcher,
                          LayerID layerID) {
  if (m_initialized) {
    m_initialized = false;
    onShutdown(entityManager, eventDispatcher, layerID);
  }
}
}  // namespace Neat