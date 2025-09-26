#include "NeatPCH.hpp"

#include "Scene.hpp"

#include "Neat/Components/CameraComponent.hpp"
#include "Neat/Components/TransformComponent.hpp"
#include "Neat/Components/LabelComponent.hpp"
#include "Neat/Components/LabelComponent.hpp"
#include "Neat/Graphics/RenderCommand.hpp"
#include "Neat/Graphics/Renderer2D.hpp"
#include "Neat/Math/Matrix.hpp"

namespace Neat {
Scene::Scene(const Ref<EventDispatcher> &eventDispatcher) {
  NT_PROFILE_FUNCTION();

  m_entityManager = makeRef<EntityManager>(eventDispatcher);
  m_systemManager = makeRef<SystemManager>(m_entityManager, eventDispatcher);
  eventDispatcher->get<ComponentAddedEvent<ActiveCameraTagComponent>>()
      .connect<&Scene::onActiveCameraTagComponentAdded>(*this);
  m_systemManager->addSystem<Render2DSystem>();
  m_systemManager->initialize();
  m_eventDispatcher = eventDispatcher;
}

Scene::~Scene() {
  NT_PROFILE_FUNCTION();

  m_eventDispatcher->disconnect(*this);
}

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

void Scene::onRuntimeUpdate(double deltaTimeSeconds) {
  NT_PROFILE_FUNCTION();

  m_systemManager->onUpdate<Render2DSystem>(deltaTimeSeconds);
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