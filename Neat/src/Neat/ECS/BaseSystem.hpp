#pragma once

#include "Neat/Core/Types.hpp"
#include "Neat/Events/EventManager.hpp"
#include "Neat/Helper/NonCopyable.hpp"

namespace Neat {
class EntityManager;

class BaseSystem : public NonCopyable {
 public:
  using Family = UInt32;

  virtual ~BaseSystem() = default;

  virtual void init(EventManager &eventManager) {}
  virtual void update(EntityManager &entityManager, EventManager &eventManager,
                      DeltaTime deltaTime) = 0;

 protected:
  static Family s_familyCounter;
};
}  // namespace Neat