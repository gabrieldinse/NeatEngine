#pragma once

#include "EditorCamera.hpp"

#include "Neat/ECS/ECS.hpp"
#include "Neat/EventDispatching/EventDispatcher.hpp"
#include "Neat/EventDispatching/EventConnectionHandles.hpp"
#include "Neat/Systems/Systems.hpp"
#include "Neat/Components/ActiveCameraTagComponent.hpp"
#include "Neat/Core/Constants.hpp"

namespace Neat {
class Scene {
 public:
  Scene(const Ref<EventDispatcher> &eventDispatcher, LayerID layerID = NoLayer);
  ~Scene();
  Entity createEntity();
  Ref<EntityManager> getEntityManager();
  Ref<SystemManager> getSystemManager();

  void onRuntimeUpdate(double deltaTimeSeconds);
  void onEditorUpdate(double deltaTimeSeconds, EditorCamera &editorCamera);
  void setViewport(UInt32 width, UInt32 height);

 private:
  bool onActiveCameraTagComponentAdded(
      const ComponentAddedEvent<ActiveCameraTagComponent> &event);

 private:
  Ref<SystemManager> m_systemManager;
  Ref<EntityManager> m_entityManager;
  Ref<EventDispatcher> m_eventDispatcher;
  EventConnectionHandles m_eventConnectionHandles;

  UInt32 m_viewportWidth{0};
  UInt32 m_viewportHeight{0};
};
}  // namespace Neat