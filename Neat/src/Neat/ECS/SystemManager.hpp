#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

#include "Neat/Core/Exceptions.hpp"
#include "Neat/Core/Log.hpp"
#include "Neat/ECS/System.hpp"
#include "Neat/Misc/NonCopyable.hpp"

namespace Neat {
class SystemManager : public NonCopyable {
 public:
  SystemManager(const std::shared_ptr<EntityManager> &entityManager,
                const std::shared_ptr<EventDispatcher> &eventDispatcher)
      : m_entityManager(entityManager), m_eventDispatcher(eventDispatcher) {}

  void init() {
    for (auto &&[family, system] : m_systems) system->init(m_eventDispatcher);

    m_initialized = true;
  }

  template <typename S>
  void addSystem(std::shared_ptr<S> system) {
    m_systems[S::getFamily()] = system;
  }

  template <typename S, typename... Args>
  std::shared_ptr<S> addSystem(Args &&...args) {
    auto system = std::make_shared<S>(std::forward<Args>(args)...);
    addSystem(system);

    return system;
  }

  template <typename S>
  std::shared_ptr<S> getSystem() {
    auto it = m_systems.find(S::getFamily());

    if (it == m_systems.end()) throw InvalidSystemError();

    auto &&[family, system] = *it;

    return std::shared_ptr<S>(std::static_pointer_cast<S>(system));
  }

  template <typename S>
  void onUpdate(DeltaTime deltaTime) {
    if (not m_initialized) throw SystemManagerNotInitializedError();

    auto system = getSystem<S>();
    system->onUpdate(m_entityManager, m_eventDispatcher, deltaTime);
  }

  void updateAll(DeltaTime deltaTime) {
    if (not m_initialized) throw SystemManagerNotInitializedError();

    for (auto &&[family, system] : m_systems)
      system->onUpdate(m_entityManager, m_eventDispatcher, deltaTime);
  }

 private:
  bool m_initialized = false;
  std::shared_ptr<EntityManager> m_entityManager;
  std::shared_ptr<EventDispatcher> m_eventDispatcher;
  std::unordered_map<BaseSystem::Family, std::shared_ptr<BaseSystem>> m_systems;
};
}  // namespace Neat