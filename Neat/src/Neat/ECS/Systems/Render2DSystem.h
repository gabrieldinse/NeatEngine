#pragma once

#include "Neat/ECS/System.h"
#include "Neat/ECS/Entity.h"
#include "Neat/ECS/Components.h"
#include "Neat/Graphics/Renderer2D.h"
#include "Neat/Graphics/RenderCommand.h"
#include "Neat/Graphics/Camera.h"


namespace Neat
{
   class Render2DSystem : public System<Render2DSystem>
   {
   public:
      Render2DSystem(Camera& camera)
         : m_camera(camera) {}

      virtual void update(EntityManager& entityManager,
         EventManager& eventManager, DeltaTime deltaTime);

   private:
      Camera& m_camera;
   };
}