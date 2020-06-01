#pragma once

#include "Neat/ECS/System.h"
#include "Neat/ECS/Entity.h"
#include "Neat/ECS/Components.h"
#include "Neat/Graphics/Renderer2D.h"
#include "Neat/Graphics/RenderCommand.h"
#include "Neat/Graphics/OrthographicCamera.h"


namespace Neat
{
   class RenderSystem : public System<RenderSystem>
   {
   public:
      RenderSystem(OrthographicCamera& camera) : m_camera(camera) {}

      virtual void update(EntityManager& entityManager,
         EventManager& eventManager, DeltaTime deltaTime)
      {
         Neat::Renderer2D::resetStats();
         Neat::RenderCommand::clearWithColor({ 0.35f, 0.35f, 0.55f, 1.0f });

         Renderer2D::beginScene(m_camera);

         ComponentHandle<Renderable> renderable;
         for (auto& entity : entityManager.entitiesWithComponents(renderable))
         {
            renderable->shape->draw();
         }

         Renderer2D::endScene();
      }

   private:
      OrthographicCamera& m_camera;
   };
}