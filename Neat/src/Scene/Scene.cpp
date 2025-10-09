#include "NeatPCH.hpp"

#include "Scene.hpp"

#include "Components/CameraComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/LabelComponent.hpp"
#include "Components/LabelComponent.hpp"
#include "Graphics/RenderCommand.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Math/Matrix.hpp"

namespace Neat {
Scene::Scene(const Ref<EventDispatcher> &eventDispatcher, LayerID layerID) {
  NT_PROFILE_FUNCTION();

  m_entityManager = makeRef<EntityManager>(eventDispatcher);
  m_systemManager = makeRef<SystemManager>();
  m_eventDispatcher = eventDispatcher;
  auto connectionHandle =
      m_eventDispatcher->get<ComponentAddedEvent<ActiveCameraTagComponent>>()
          .connectScoped<&Scene::onActiveCameraTagComponentAdded>(
              *this, EventPriorityLowest, layerID);
  m_eventConnectionHandles.add(connectionHandle);
  m_systemManager->addSystem<Render2DSystem>();
  m_systemManager->addSystem<Physics2DSystem>();
  m_systemManager->onInitialize<Render2DSystem>(m_entityManager,
                                                m_eventDispatcher);
}

Scene::~Scene() { NT_PROFILE_FUNCTION(); }

Entity Scene::createEntity() { return m_entityManager->createEntity(); }

Ref<EntityManager> Scene::getEntityManager() { return m_entityManager; }

Ref<SystemManager> Scene::getSystemManager() { return m_systemManager; }

void Scene::setViewport(UInt32 width, UInt32 height) {
  NT_PROFILE_FUNCTION();

  m_viewportWidth = width;
  m_viewportHeight = height;
  for (auto cameraEntity :
       m_entityManager->entitiesWithComponents<ActiveCameraTagComponent,
                                               CameraComponent>()) {
    cameraEntity.getComponent<CameraComponent>()->setAspectRatio(width, height);
    return;
  }
}

void Scene::onRuntimeStart() {
  NT_PROFILE_FUNCTION();

  m_systemManager->onInitialize<Physics2DSystem>(m_entityManager,
                                                 m_eventDispatcher);
}

void Scene::onRuntimeStop() {
  NT_PROFILE_FUNCTION();

  m_systemManager->onShutdown<Physics2DSystem>(m_entityManager,
                                               m_eventDispatcher);
}

void Scene::onRuntimeUpdate(double deltaTimeSeconds) {
  NT_PROFILE_FUNCTION();

  m_systemManager->onUpdate<Physics2DSystem>(m_entityManager, m_eventDispatcher,
                                             deltaTimeSeconds);
  m_systemManager->onUpdate<Render2DSystem>(m_entityManager, m_eventDispatcher,
                                            deltaTimeSeconds);
}

void Scene::onEditorUpdate([[maybe_unused]] double deltaTimeSeconds,
                           EditorCamera &editorCamera) {
  NT_PROFILE_FUNCTION();

  Renderer2D::resetStats();
  RenderCommand::clearWithColor(Color::lightSlateGray);
  Renderer2D::beginScene(editorCamera.getCamera(), editorCamera.getTransform());

  ComponentHandle<RenderableSpriteComponent> renderableSprite;
  ComponentHandle<TransformComponent> transform;
  for (auto entity :
       m_entityManager->entitiesWithComponents(renderableSprite, transform)) {
    Renderer2D::drawSprite(*transform, *renderableSprite, entity);
  }
  Renderer2D::endScene();
}

bool Scene::onActiveCameraTagComponentAdded(
    [[maybe_unused]] const ComponentAddedEvent<ActiveCameraTagComponent>
        &event) {
  setViewport(m_viewportWidth, m_viewportHeight);
  return false;
}

};  // namespace Neat