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

  virtual void init(const std::shared_ptr<EventManager> &eventManager) {}
  virtual void onUpdate(const std::shared_ptr<EntityManager> &entityManager,
                        const std::shared_ptr<EventManager> &eventManager,
                        DeltaTime deltaTime) = 0;

 protected:
  static Family s_familyCounter;
};
}  // namespace Neat