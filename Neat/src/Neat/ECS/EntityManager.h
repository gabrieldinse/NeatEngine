#pragma  once

#include <vector>
#include <queue>
#include <bitset>

#include "Neat/Core/Log.h"
#include "Neat/Core/Types.h"
#include "Neat/ECS/EntityManager.h"
#include "Neat/ECS/Config.h"
#include "Neat/ECS/Entity.h"
#include "Neat/ECS/MemoryPool.h"
#include "Neat/ECS/Component.h"
#include "Neat/ECS/ComponentHandle.h"
#include "Neat/Events/Event.h"
#include "Neat/Events/EventManager.h"


namespace Neat
{

   // ---------------------------------------------------------------------- //
   // Custom ECS events ---------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   struct EntityCreatedEvent
   {
      explicit EntityCreatedEvent(const Entity& entity)
         : entity(entity) {}
      virtual ~EntityCreatedEvent() {}

      Entity entity;
   };


   struct EntityDestroyedEvent
   {
      explicit EntityDestroyedEvent(const Entity& entity)
         : entity(entity) {}
      virtual ~EntityDestroyedEvent() {}

      Entity entity;
   };


   template <typename C>
   struct ComponentAddedEvent
   {
      ComponentAddedEvent(const Entity& entity,
         const ComponentHandle<C>& component)
         : entity(entity), component(component) {}

      Entity entity;
      ComponentHandle<C> component;
   };


   template <typename C>
   struct ComponentRemovedEvent
   {
      ComponentRemovedEvent(const Entity& entity,
         const ComponentHandle<C>& component)
         : entity(entity), component(component) {}

      Entity entity;
      ComponentHandle<C> component;
   };


   // ---------------------------------------------------------------------- //
   // EntityManager -------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class EntityManager
   {
   public:


   public:
      EntityManager(EventManager& eventManager)
         : m_eventManager(eventManager)
      {
      }

      ~EntityManager()
      {
         reset();
      }

      UInt size() const
      {
         return
            (UInt)(m_entityComponentMasks.size() - m_freeEntityIds.size());
      }

      UInt capacity() const
      {
         return (UInt)(m_entityComponentMasks.size());
      }

      bool isValid(Entity::Id id)
      {
         return
            id.index() < m_entityIdsVersion.size() &&
            m_entityIdsVersion[id.index()] == id.version();
      }


      Entity create()
      {
         UInt index;
         UInt version;

         if (m_freeEntityIds.empty())
         {
            index = m_indexCounter++;
            accomodateEntity(index);
            version = m_entityIdsVersion[index] = 1;
         }
         else
         {
            index = m_freeEntityIds.front();
            m_freeEntityIds.pop();
            version = m_entityIdsVersion[index];
         }

         Entity entity(this, Entity::Id(index, version));
         m_eventManager.publish<EntityCreatedEvent>(entity);

         return entity;
      }

      void destroy(Entity::Id id)
      {
         checkIsValid(id);

         UInt index = id.index();
         auto component_mask = m_entityComponentMasks[index];

         m_eventManager.publish<EntityDestroyedEvent>(Entity(this, id));

         for (std::size_t i = 0; i < m_componentArrays.size(); ++i)
         {
            BaseMemoryPool* component_array = m_componentArrays[i];
            if ((component_array != nullptr) && component_mask.test(i))
               component_array->destroy(index);
         }

         m_entityComponentMasks[index].reset();
         ++m_entityIdsVersion[index];
         m_freeEntityIds.push(index);
      }

      Entity get(Entity::id id)
      {

      }
      
   private:
      friend class Entity;

      template <typename C, typename EM>
      friend class ComponentHandle;

      void checkIsValid(Entity::Id id)
      {
         if (id.index() >= m_entityIdsVersion.size())
            throw InvalidEntityError(
               "Entity::Id outside entity vector range.");

         if (m_entityIdsVersion[id.index()] != id.version())
            throw InvalidEntityError(
               "Attempt to access entity via a stale Entity::Id.");
      }


      template <typename C>
      C* getComponentPtr(Entity::Id id)
      {
         checkIsValid(id);

         auto* component_array = m_componentArrays[getComponentFamily<C>()];
         NT_CORE_ASSERT(component_array != nullptr,
            "Entity does not have this component.");

         return static_cast<C*>(component_array[id.index()]);
      }

      template <typename C>
      const C* getComponentPtr(Entity::Id id) const
      {
         checkIsValid(id);

         auto* component_array = m_componentArrays[getComponentFamily<C>()];
         NT_CORE_ASSERT(component_array != nullptr,
            "Entity does not have this component.");

         return static_cast<const C*>(component_array[id.index()]);
      }


      ComponentMask getComponentMask(Entity::Id id)
      {
         checkIsValid(id);

         return m_entityComponentMasks.at(id.index());
      }

      template <typename C>
      ComponentMask createComponentMask()
      {
         ComponentMask mask;
         mask.set(getComponentFamily<C>());

         return mask;
      }

      template <typename C1, typename C2, typename... Others>
      ComponentMask createComponentMask()
      {
         return
            createComponentMask<C1>() | createComponentMask<C2, Others...>();
      }

      template <typename C>
      ComponentMask createComponentMask(
         const ComponentHandle<C>& componentHandle)
      {
         return createComponentMask<C>();
      }

      template <typename C1, typename... Others>
      ComponentMask createComponentMask(
         const ComponentHandle<C1>& componentHandle1,
         const ComponentHandle<Others>&... others)
      {
         return createComponentMask<C1, Others...>();
      }


      void accomodateEntity(UInt index)
      {
         if (m_entityComponentMasks.size() <= index)
         {
            m_entityComponentMasks.resize(index + 1);
            m_entityIdsVersion.resize(index + 1);

            for (BaseMemoryPool* component_array : m_componentArrays)
               if (component_array)
                  component_array->resize(index + 1);
         }
      }

      template <typename C>
      MemoryPool<C>* accomodateComponent()
      {
         BaseComponent::Family family = getComponentFamily<C>();

         if (m_componentArrays.size() <= family)
            m_componentArrays.resize(family + 1, nullptr);

         if (m_componentArrays[family] == nullptr)
         {
            auto* component_array = new MemoryPool<C>();
            component_array->resize(m_indexCounter);
            m_componentArrays[family] = component_array;
         }

         return static_cast<MemoryPool<C>*>(m_componentArrays[family]);
      }

   private:
      UInt m_indexCounter = 0;

      EventManager& m_eventManager;
      std::vector<BaseMemoryPool*> m_componentArrays;
      std::vector<ComponentMask> m_entityComponentMasks;
      std::vector<UInt> m_entityIdsVersion;
      std::queue<UInt> m_freeEntityIds;
   };
}
