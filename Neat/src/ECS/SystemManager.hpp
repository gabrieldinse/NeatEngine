#pragma once

#include <unordered_map>
#include <utility>
#include <optional>

#include "System.hpp"

#include "Utils/NonCopyable.hpp"

namespace Neat {
class SystemManager : public NonCopyable {
 public:
  SystemManager() = default;

  void initialize(const Ref<EntityManager> &entityManager,
                  const Ref<EventDispatcher> &eventDispatcher,
                  LayerID layerID = NoneLayer) {
    for (auto &&[family, system] : m_systems) {
      system->initialize(entityManager, eventDispatcher, layerID);
    }
  }

  template <typename S>
  void initialize(const Ref<EntityManager> &entityManager,
                  const Ref<EventDispatcher> &eventDispatcher,
                  LayerID layerID = NoneLayer) {
    if (auto system = getSystem<S>()) {
      (*system)->initialize(entityManager, eventDispatcher, layerID);
    }
  }

  void shutdown(const Ref<EntityManager> &entityManager,
                const Ref<EventDispatcher> &eventDispatcher,
                LayerID layerID = NoneLayer) {
    for (auto &&[family, system] : m_systems) {
      system->shutdown(entityManager, eventDispatcher, layerID);
    }
  }

  template <typename S>
  void shutdown(const Ref<EntityManager> &entityManager,
                const Ref<EventDispatcher> &eventDispatcher,
                LayerID layerID = NoneLayer) {
    if (auto system = getSystem<S>()) {
      (*system)->shutdown(entityManager, eventDispatcher, layerID);
    }
  }

  template <typename S>
  void addSystem(Ref<S> system) {
    m_systems[S::getFamily()] = system;
  }

  template <typename S, typename... Args>
  Ref<S> addSystem(Args &&...args) {
    auto system = makeRef<S>(std::forward<Args>(args)...);
    addSystem(system);

    return system;
  }

  template <typename S>
  std::optional<Ref<S>> getSystem() {
    auto it = m_systems.find(S::getFamily());

    if (it == m_systems.end()) {
      return std::nullopt;
    }

    auto &&[family, system] = *it;

    return staticCast<S>(system);
  }

  template <typename S>
  void update(const Ref<EntityManager> &entityManager,
              const Ref<EventDispatcher> &eventDispatcher,
              double deltaTimeSeconds, LayerID layerID = NoneLayer) {
    if (auto system = getSystem<S>()) {
      (*system)->update(entityManager, eventDispatcher, deltaTimeSeconds,
                        layerID);
    }
  }

  void updateAll(const Ref<EntityManager> &entityManager,
                 const Ref<EventDispatcher> &eventDispatcher,
                 double deltaTimeSeconds, LayerID layerID = NoneLayer) {
    for (auto &&[family, system] : m_systems) {
      system->update(entityManager, eventDispatcher, deltaTimeSeconds, layerID);
    }
  }

 private:
  std::unordered_map<BaseSystem::Family, Ref<BaseSystem>> m_systems;
};
}  // namespace Neat