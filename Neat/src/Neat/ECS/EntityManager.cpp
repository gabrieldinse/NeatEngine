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
   EntityManager::EntityManager(EventManager& eventManager)
      : m_eventManager(eventManager)
   {
   }

   EntityManager::~EntityManager()
   {
      reset();
   }

   bool EntityManager::isValid(Entity::Id id)
   {
      return
         id.index() < m_entityIdsVersion.size() &&
         m_entityIdsVersion[id.index()] == id.version();
   }

   void EntityManager::checkIsValid(Entity::Id id)
   {
      if (id.index() >= m_entityIdsVersion.size())
         throw InvalidEntityError(
            "Entity::Id outside entity vector range.");

      if (m_entityIdsVersion[id.index()] != id.version())
         throw InvalidEntityError(
            "Attempt to access entity via a stale Entity::Id.");
   }


   template <typename C>
   C* EntityManager::getComponentPtr(Entity::Id id)
   {
      checkIsValid(id);

      auto* component_array = m_componentArrays[getComponentFamily<C>()];
      NT_CORE_ASSERT(component_array != nullptr,
         "Entity does not have this component.");

      return static_cast<C*>(component_array[id.index()]);
   }

   template <typename C>
   const C* EntityManager::getComponentPtr(Entity::Id id) const
   {
      checkIsValid(id);

      auto* component_array = m_componentArrays[getComponentFamily<C>()];
      NT_CORE_ASSERT(component_array != nullptr,
         "Entity does not have this component.");

      return static_cast<const C*>(component_array[id.index()]);
   }


   ComponentMask EntityManager::getComponentMask(Entity::Id id)
   {
      checkIsValid(id);

      return m_entityComponentMasks.at(id.index());
   }

   template <typename C>
   ComponentMask EntityManager::createComponentMask()
   {
      ComponentMask mask;
      mask.set(getComponentFamily<C>());

      return mask;
   }

   template <typename C1, typename C2, typename... Others>
   ComponentMask EntityManager::createComponentMask()
   {
      return
         createComponentMask<C1>() | createComponentMask<C2, Others...>();
   }

   template <typename C>
   ComponentMask EntityManager::createComponentMask(
      const ComponentHandle<C>& componentHandle)
   {
      return createComponentMask<C>();
   }

   template <typename C1, typename... Others>
   ComponentMask EntityManager::createComponentMask(
      const ComponentHandle<C1>& componentHandle1,
      const ComponentHandle<Others>&... others)
   {
      return createComponentMask<C1, Others...>();
   }


   void EntityManager::accomodateEntity(UInt index)
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
   MemoryPool<C>* EntityManager::accomodateComponent()
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

      return static_cast<Pool<C>*>(m_componentArrays[family]);
   }
}
