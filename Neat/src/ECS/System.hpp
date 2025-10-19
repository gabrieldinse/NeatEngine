#pragma once

#include "BaseSystem.hpp"

namespace Neat {
class SystemManager;
class EntityManager;

template <typename DerivedSystem>
class System : public BaseSystem {
 public:
  virtual ~System() = default;

  virtual void onInitialize(
      [[maybe_unused]] const Ref<EntityManager> &entityManager,
      [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
      [[maybe_unused]] LayerID layerID = NoneLayer) override {}
  virtual void onShutdown(
      [[maybe_unused]] const Ref<EntityManager> &entityManager,
      [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
      [[maybe_unused]] LayerID layerID = NoneLayer) override {}
  virtual void onUpdate(
      [[maybe_unused]] const Ref<EntityManager> &entityManager,
      [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
      [[maybe_unused]] double deltaTimeSeconds,
      [[maybe_unused]] LayerID layerID = NoneLayer) override {}

 private:
  friend class SystemManager;

  static Family getFamily() {
    static Family family = s_familyCounter++;
    return family;
  }
};
}  // namespace Neat