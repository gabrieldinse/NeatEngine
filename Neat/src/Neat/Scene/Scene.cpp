#include "NeatPCH.hpp"

#include "Neat/Scene/Scene.hpp"
#include "Neat/Components/CameraComponent.hpp"
#include "Neat/Components/TransformComponent.hpp"
#include "Neat/Components/ActiveCameraTagComponent.hpp"

namespace Neat {
Scene::Scene(const Ref<EventDispatcher> &eventDispatcher) {
  m_entities = makeRef<EntityManager>(eventDispatcher);
  m_systems = makeRef<SystemManager>(m_entities, eventDispatcher);

  m_camera = m_entities->createEntity();
  m_camera.addComponent<CameraComponent>(OrthographicProperties{1280, 720});
  m_camera.addComponent<TransformComponent>();
  m_camera.addComponent<ActiveCameraTagComponent>();

  m_systems->addSystem<OrthographicCameraControllerSystem>(m_camera);
  m_systems->addSystem<Render2DSystem>();
  m_systems->initialize();
}

Scene::~Scene() {}

Entity Scene::createEntity() { return m_entities->createEntity(); }

Ref<EntityManager> Scene::getEntityManager() { return m_entities; }

Ref<SystemManager> Scene::getSystems() { return m_systems; }

void Scene::setViewport(UInt32 width, UInt32 height) {
  auto camera_controller =
      m_systems->getSystem<OrthographicCameraControllerSystem>();
  if (camera_controller) {
    (*camera_controller)->setAspectRatio(width, height);
  }
}

void Scene::onUpdate(double deltaTimeSeconds) {
  m_systems->onUpdate<Render2DSystem>(deltaTimeSeconds);
}
};  // namespace Neat