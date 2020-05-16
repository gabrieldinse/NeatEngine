#pragma once

#include "Neat/Core/Types.h"
#include "Neat/Events/EventManager.h"


namespace Neat
{
   class SystemManager;
   class EventManager;
   class EntityManager;

   // ---------------------------------------------------------------------- //
   // BaseSystem ----------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class BaseSystem
   {
   public:
      using Family = UIntLong;

      BaseSystem() = default;
      virtual ~BaseSystem() = default;

      BaseSystem(const BaseSystem&) = delete;
      BaseSystem& operator = (const BaseSystem &) = delete;

      virtual void init(EventManager& eventManager) {}
      virtual void update(EntityManager& entityManager,
         EventManager& eventManager, Timestep deltaTime) = 0;
      virtual void render(EntityManager& entityManager,
         EventManager& eventManager) = 0;

   protected:
      static Family s_familyCounter;
   };


   // ---------------------------------------------------------------------- //
   // System --------------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   template <typename DerivedSystem>
   class System : public BaseSystem
   {
   public:
      virtual ~System() = default;

      virtual void update(EntityManager& entityManager,
         EventManager& eventManager, Timestep deltaTime) override {}
      virtual void render(EntityManager& entityManager,
         EventManager& eventManager) override {}

   private:
      friend class SystemManager;

      static Family getFamily()
      {
         static Family family = s_familyCounter++;
         return family;
      }
   };
}