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

  virtual void initialize(const Ref<EntityManager> &entityManager,
                          const Ref<EventDispatcher> &eventDispatcher,
                          LayerID layerID) = 0;
  virtual void onUpdate(const Ref<EntityManager> &entityManager,
                        const Ref<EventDispatcher> &eventDispatcher,
                        double deltaTimeSeconds, LayerID layerID) = 0;

 protected:
  static Family s_familyCounter;
};
}  // namespace Neat