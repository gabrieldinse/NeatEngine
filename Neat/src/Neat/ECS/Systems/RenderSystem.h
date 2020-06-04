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
      RenderSystem(OrthographicCamera& camera)
         : m_camera(camera) {}

      virtual void update(EntityManager& entityManager,
         EventManager& eventManager, DeltaTime deltaTime);

   private:
      OrthographicCamera& m_camera;
   };
}