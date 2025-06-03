#pragma once

#include "Neat/ECS/BaseSystem.hpp"

namespace Neat {
class SystemManager;
class EntityManager;

template <typename DerivedSystem>
class System : public BaseSystem {
 public:
  virtual ~System() = default;

  virtual void onUpdate(const std::shared_ptr<EntityManager> &entityManager,
                        const std::shared_ptr<EventManager> &eventManager,
                        DeltaTime deltaTime) override {}

 private:
  friend class SystemManager;

  static Family getFamily() {
    static Family family = s_familyCounter++;
    return family;
  }
};
}  // namespace Neat