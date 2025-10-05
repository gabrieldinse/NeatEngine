#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include <optional>

#include "System.hpp"

#include "Core/Exceptions.hpp"
#include "Core/Log.hpp"
#include "Utils/NonCopyable.hpp"

namespace Neat {
class SystemManager : public NonCopyable {
 public:
  SystemManager() = default;

  void initialize(const Ref<EntityManager> &entityManager,
                  const Ref<EventDispatcher> &eventDispatcher,
                  LayerID layerID = NoLayer) {
    for (auto &&[family, system] : m_systems) {
      system->initialize(entityManager, eventDispatcher, layerID);
    }
    m_initialized = true;
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

    return Ref<S>(std::static_pointer_cast<S>(system));
  }

  template <typename S>
  void onUpdate(const Ref<EntityManager> &entityManager,
                const Ref<EventDispatcher> &eventDispatcher,
                double deltaTimeSeconds, LayerID layerID = NoLayer) {
    if (not m_initialized) {
      initialize(entityManager, eventDispatcher, layerID);
    }

    if (auto system = getSystem<S>()) {
      (*system)->onUpdate(entityManager, eventDispatcher, deltaTimeSeconds);
    }
  }

  void updateAll(const Ref<EntityManager> &entityManager,
                 const Ref<EventDispatcher> &eventDispatcher,
                 double deltaTimeSeconds, LayerID layerID = NoLayer) {
    if (not m_initialized) {
      initialize(entityManager, eventDispatcher, layerID);
    }

    for (auto &&[family, system] : m_systems) {
      system->onUpdate(entityManager, eventDispatcher, deltaTimeSeconds,
                       layerID);
    }
  }

 private:
  bool m_initialized = false;
  std::unordered_map<BaseSystem::Family, Ref<BaseSystem>> m_systems;
};
}  // namespace Neat