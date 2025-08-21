#include "NeatPCH.hpp"

#include "Neat/Scene/Scene.hpp"

namespace Neat {
Scene::Scene(const Ref<EventDispatcher> &eventDispatcher) {
  m_entities = makeRef<EntityManager>(eventDispatcher);
  m_systems = makeRef<SystemManager>(m_entities, eventDispatcher);
  m_camera = makeRef<OrthographicCamera>(Vector2F{0.0f, 0.0f}, 1280u, 720u);
  auto camera_controller_system =
      m_systems->addSystem<OrthographicCameraControllerSystem>(m_camera);
  m_systems->addSystem<Render2DSystem>(m_camera);
  m_systems->init();
}

Scene::~Scene() {}

Entity Scene::createEntity() { return m_entities->createEntity(); }

Ref<EntityManager> Scene::getEntityManager() { return m_entities; }

Ref<SystemManager> Scene::getSystems() { return m_systems; }

void Scene::setViewport(UInt32 width, UInt32 height) {
  m_camera->setAspectRatio(width, height);
}

void Scene::onUpdate(double deltaTimeSeconds) {
  m_systems->onUpdate<Render2DSystem>(deltaTimeSeconds);
}
};  // namespace Neat