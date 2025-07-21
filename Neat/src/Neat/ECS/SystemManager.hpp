#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

#include "Neat/Core/Exceptions.hpp"
#include "Neat/Core/Log.hpp"
#include "Neat/ECS/System.hpp"
#include "Neat/Utils/NonCopyable.hpp"

namespace Neat {
class SystemManager : public NonCopyable {
 public:
  SystemManager(const Ref<EntityManager> &entityManager,
                const Ref<EventDispatcher> &eventDispatcher)
      : m_entityManager(entityManager), m_eventDispatcher(eventDispatcher) {}

  void init() {
    for (auto &&[family, system] : m_systems) system->init(m_eventDispatcher);

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
  Ref<S> getSystem() {
    auto it = m_systems.find(S::getFamily());

    if (it == m_systems.end()) {
      throw InvalidSystemError();
    }

    auto &&[family, system] = *it;

    return Ref<S>(std::static_pointer_cast<S>(system));
  }

  template <typename S>
  void onUpdate(double deltaTimeSeconds) {
    if (not m_initialized) {
      throw SystemManagerNotInitializedError();
    }

    auto system = getSystem<S>();
    system->onUpdate(m_entityManager, m_eventDispatcher, deltaTimeSeconds);
  }

  void updateAll(double deltaTimeSeconds) {
    if (not m_initialized) throw SystemManagerNotInitializedError();

    for (auto &&[family, system] : m_systems) {
      system->onUpdate(m_entityManager, m_eventDispatcher, deltaTimeSeconds);
    }
  }

 private:
  bool m_initialized = false;
  Ref<EntityManager> m_entityManager;
  Ref<EventDispatcher> m_eventDispatcher;
  std::unordered_map<BaseSystem::Family, Ref<BaseSystem>> m_systems;
};
}  // namespace Neat