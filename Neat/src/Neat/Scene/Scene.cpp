#include "NeatPCH.hpp"

#include "Scene.hpp"

#include "Neat/Components/CameraComponent.hpp"
#include "Neat/Components/TransformComponent.hpp"
#include "Neat/Components/LabelComponent.hpp"
#include "Neat/Components/LabelComponent.hpp"

namespace Neat {
Scene::Scene(const Ref<EventDispatcher> &eventDispatcher) {
  m_entityManager = makeRef<EntityManager>(eventDispatcher);
  m_systems = makeRef<SystemManager>(m_entityManager, eventDispatcher);
  eventDispatcher->get<ComponentAddedEvent<ActiveCameraTagComponent>>()
      .connect<&Scene::onActiveCameraTagComponentAdded>(*this);
  m_systems->addSystem<OrthographicCameraControllerSystem>();
  m_systems->addSystem<Render2DSystem>();
  m_systems->initialize();
}

Scene::~Scene() {}

Entity Scene::createEntity() { return m_entityManager->createEntity(); }

Ref<EntityManager> Scene::getEntityManager() { return m_entityManager; }

Ref<SystemManager> Scene::getSystems() { return m_systems; }

void Scene::setViewport(UInt32 width, UInt32 height) {
  m_viewportWidth = width;
  m_viewportHeight = height;
  for (auto cameraEntity :
       m_entityManager->entitiesWithComponents<ActiveCameraTagComponent,
                                               CameraComponent>()) {
    cameraEntity.getComponent<CameraComponent>()->setOrthographicAspectRatio(
        width, height);
    return;
  }
}

void Scene::onUpdate(double deltaTimeSeconds) {
  m_systems->onUpdate<Render2DSystem>(deltaTimeSeconds);
}

bool Scene::onActiveCameraTagComponentAdded(
    [[maybe_unused]] const ComponentAddedEvent<ActiveCameraTagComponent>
        &event) {
  setViewport(m_viewportWidth, m_viewportHeight);
  return false;
}

};  // namespace Neat