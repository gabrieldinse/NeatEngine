#pragma once

#include "Neat/ECS/ECS.hpp"
#include "Neat/Systems/Systems.hpp"

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
  Ref<SystemManager> m_systems;
  Ref<EntityManager> m_entities;
  Ref<OrthographicCamera> m_camera;
};
}  // namespace Neat