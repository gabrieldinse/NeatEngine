#include "NeatPCH.hpp"

#include "Render2DSystem.hpp"

#include "ECS/EntityManager.hpp"
#include "Graphics/RenderCommand.hpp"
#include "Graphics/Renderer2D.hpp"
#include "Components/RenderableSpriteComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/CameraComponent.hpp"
#include "Components/ActiveCameraTagComponent.hpp"

namespace Neat {
void Render2DSystem::update(
    const Ref<EntityManager> &entityManager,
    [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
    [[maybe_unused]] double deltaTimeSeconds,
    [[maybe_unused]] LayerID layerID) {
  NT_PROFILE_FUNCTION();

  Renderer2D::resetStats();
  RenderCommand::clearWithColor(Color::lightSlateGray);

  for (auto activeCameraEntity :
       entityManager->entitiesWithComponents<
           ActiveCameraTagComponent, CameraComponent, TransformComponent>()) {
    auto camera = activeCameraEntity.getComponent<CameraComponent>();
    auto cameraTransform =
        activeCameraEntity.getComponent<TransformComponent>();
    Renderer2D::beginScene(*camera, *cameraTransform);

    ComponentHandle<RenderableSpriteComponent> renderableSprite;
    ComponentHandle<TransformComponent> transform;
    for (auto entity :
         entityManager->entitiesWithComponents(renderableSprite, transform)) {
      Renderer2D::drawSprite(*transform, *renderableSprite, entity);
    }
    Renderer2D::endScene();
    break;
  }
}
}  // namespace Neat