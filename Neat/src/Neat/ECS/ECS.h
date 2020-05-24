#pragma once

#include "Neat/ECS/Entity.h"
#include "Neat/ECS/SystemManager.h"


namespace Neat
{
   EntityManager& entities();
   SystemManager& systems();

   struct ECS
   {
      ECS(EventManager& eventManager = events())
         : entities(eventManager), systems(entities, eventManager) {}

      EntityManager entities;
      SystemManager systems;

   private:
      friend EntityManager& entities();
      friend SystemManager& systems();

   private:
      static std::unique_ptr<ECS> s_instance;
   };
}