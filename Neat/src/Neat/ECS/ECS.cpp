#include "Neat/ECS/ECS.h"


namespace Neat
{
   std::unique_ptr<ECS> ECS::s_instance;

   EntityManager& entities()
   {
      if (ECS::s_instance == nullptr)
         ECS::s_instance = std::make_unique<ECS>();

      return ECS::s_instance->entities;
   }

   SystemManager& systems()
   {
      if (ECS::s_instance == nullptr)
         ECS::s_instance = std::make_unique<ECS>();

      return ECS::s_instance->systems;
   }
}