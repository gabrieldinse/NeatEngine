#pragma  once

#include <vector>
#include <bitset>

#include "Neat/Core/Log.h"
#include "Neat/Core/Types.h"



namespace Neat
{
   class EventManager;
   class BaseMemoryPool;


   // ---------------------------------------------------------------------- //
   // Custom ECS events ---------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   struct EntityCreatedEvent
   {
      Entity entity;

      explicit EntityCreatedEvent(const Entity& entity) : entity(entity) {}
      virtual ~EntityCreatedEvent() {}
   };


   struct EntityDestroyedEvent
   {
      Entity entity;

      explicit EntityDestroyedEvent(const Entity& entity) : entity(entity) {}
      virtual ~EntityDestroyedEvent() {}
   };


   template <typename C>
   struct ComponentAddedEvent
   {
     ComponentAddedEvent(const Entity& entity,
        const ComponentHandle<C>& component) :
         entity(entity), component(component) {}

     Entity entity;
     ComponentHandle<C> component;
   };


   template <typename C>
   struct ComponentRemovedEvent
   {
     ComponentRemovedEvent(const Entity& entity,
        const ComponentHandle<C>& component) :
         entity(entity), component(component) {}

     Entity entity;
     ComponentHandle<C> component;
   };


   // ---------------------------------------------------------------------- //
   // EntityManager -------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class EntityManager
   {
   public:
      using ComponentMask = std::bitset<NT_MAX_COMPONENTS>;

   public:
      explicit EntityManager(EventManager& eventManager);
      virtual ~EntityManager();

      bool isValid(Entity::Id id);
      
   private:
      friend class Entity;

      template <typename C, typename EM>
      friend class ComponentHandle;

      void checkIsValid(Entity::Id id);

      template <typename C>
      C* getComponentPtr(Entity::Id id);

      template <typename C>
      const C* getComponentPtr(Entity::Id id) const;

      ComponentMask getComponentMask(Entity::Id id);

      template <typename C>
      ComponentMask createComponentMask();

      template <typename C1, typename C2, typename... Others>
      ComponentMask createComponentMask();

      template <typename C>
      ComponentMask createComponentMask(
         const ComponentHandle<C>& componentHandle);

      template <typename C1, typename... Others>
      ComponentMask createComponentMask(
         const ComponentHandle<C1>& componentHandle1,
         const ComponentHandle<Others>&... others);

      void accomodateEntity(UInt index);

      template <typename C>
      MemoryPool<C>* accomodateComponent();

   private:
      UInt m_indexCounter = 0;

      EventManager& m_eventManager;
      std::vector<BaseMemoryPool*> m_componentArrays;
      std::vector<ComponentMask> m_entityComponentMasks;
      std::vector<UInt> m_entityIdsVersion;
      std::vector<UInt> m_freeEntityIdsList;
   };
}
