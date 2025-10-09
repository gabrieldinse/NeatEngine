#pragma once

#include "Core/Types.hpp"
#include "EventDispatching/EventDispatcher.hpp"
#include "Utils/NonCopyable.hpp"

namespace Neat {
class EntityManager;

class BaseSystem : public NonCopyable {
 public:
  using Family = UInt32;

  virtual ~BaseSystem() = default;
  void onInitialize(const Ref<EntityManager> &entityManager,
                    const Ref<EventDispatcher> &eventDispatcher,
                    LayerID layerID = NoLayer);
  void onShutdown(const Ref<EntityManager> &entityManager,
                  const Ref<EventDispatcher> &eventDispatcher,
                  LayerID layerID = NoLayer);
  void onUpdate(const Ref<EntityManager> &entityManager,
                const Ref<EventDispatcher> &eventDispatcher,
                double deltaTimeSeconds, LayerID layerID = NoLayer);
  bool isInitialized() const { return m_initialized; }
  bool isShutdown() const { return not m_initialized; }

 protected:
  virtual void initialize(const Ref<EntityManager> &entityManager,
                          const Ref<EventDispatcher> &eventDispatcher,
                          LayerID layerID) = 0;
  virtual void shutdown(const Ref<EntityManager> &entityManager,
                        const Ref<EventDispatcher> &eventDispatcher,
                        LayerID layerID) = 0;
  virtual void update(const Ref<EntityManager> &entityManager,
                      const Ref<EventDispatcher> &eventDispatcher,
                      double deltaTimeSeconds, LayerID layerID) = 0;

 protected:
  bool m_initialized = false;
  static Family s_familyCounter;
};
}  // namespace Neat