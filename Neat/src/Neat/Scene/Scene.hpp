#pragma once

#include "Neat/ECS/ECS.hpp"
#include "Neat/Systems/Systems.hpp"
#include "Neat/Components/ActiveCameraTagComponent.hpp"

namespace Neat {
class Scene {
 public:
  Scene(const Ref<EventDispatcher> &eventDispatcher);
  ~Scene();
  Entity createEntity();
  Ref<EntityManager> getEntityManager();
  Ref<SystemManager> getSystems();

  void onUpdate(double deltaTimeSeconds);
  void setViewport(UInt32 width, UInt32 height);

 private:
  bool onActiveCameraTagComponentAdded(
      const ComponentAddedEvent<ActiveCameraTagComponent> &event);

 private:
  Ref<SystemManager> m_systems;
  Ref<EntityManager> m_entityManager;
  Ref<EventDispatcher> m_eventDispatcher;
  UInt32 m_viewportWidth{0};
  UInt32 m_viewportHeight{0};
};
}  // namespace Neat