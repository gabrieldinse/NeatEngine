#pragma once

#include "Neat/Core/Types.hpp"
#include "Neat/Events/EventDispatcher.hpp"
#include "Neat/Misc/NonCopyable.hpp"

namespace Neat {
class EntityManager;

class BaseSystem : public NonCopyable {
 public:
  using Family = UInt32;

  virtual ~BaseSystem() = default;

  virtual void init(const std::shared_ptr<EventDispatcher> &eventDispatcher) {}
  virtual void onUpdate(const std::shared_ptr<EntityManager> &entityManager,
                        const std::shared_ptr<EventDispatcher> &eventDispatcher,
                        DeltaTime deltaTime) = 0;

 protected:
  static Family s_familyCounter;
};
}  // namespace Neat