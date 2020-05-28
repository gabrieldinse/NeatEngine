#pragma once

#include "Neat/ECS/Entity.h"
#include "Neat/ECS/SystemManager.h"


namespace Neat
{
   struct ECS
   {
      ECS(EventManager& eventManager)
         : entities(eventManager), systems(entities, eventManager) {}

      EntityManager entities;
      SystemManager systems;
   };
}