#pragma once

#include "Neat/ECS/BaseSystem.hpp"

namespace Neat {
class SystemManager;
class EntityManager;

template <typename DerivedSystem>
class System : public BaseSystem {
 public:
  virtual ~System() = default;

  virtual void init(
      [[maybe_unused]] Ref<EntityManager> &entityManager,
      [[maybe_unused]] Ref<EventDispatcher> &eventDispatcher) override {}
  virtual void onUpdate([[maybe_unused]] Ref<EntityManager> &entityManager,
                        [[maybe_unused]] Ref<EventDispatcher> &eventDispatcher,
                        [[maybe_unused]] double deltaTimeSeconds) override {}

 private:
  friend class SystemManager;

  static Family getFamily() {
    static Family family = s_familyCounter++;
    return family;
  }
};
}  // namespace Neat