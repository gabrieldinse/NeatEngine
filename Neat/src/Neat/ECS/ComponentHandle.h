#pragma once

#include "Neat/Core/Log.h"
#include "Neat/ECS/Entity.h"


namespace Neat
{


   template <typename C, typename EM>
   class ComponentHandle
   {
   public:
      ComponentHandle() : m_entityManager(nullptr) {}

      explicit operator bool() const { return isValid(); }

      bool isValid() const
      {
         return
            m_entityManager != nullptr &&
            !m_entityManager->isValid(m_id) &&
            m_entityManager->hasComponent<C>(m_id);
      }


      C* operator->()
      {
         checkIsValid();

         return m_entityManager->getComponentPtr<C>(m_id);
      }

      const C* operator->() const
      {
         checkIsValid();

         return m_entityManager->getComponentPtr<C>(m_id);
      }

      C* get()
      {
         checkIsValid();

         return m_entityManager->getComponentPtr<C>(m_id);
      }

      const C* get() const
      {
         checkIsValid();

         return m_entityManager->getComponentPtr<C>(m_id);
      }


      void remove()
      {
         checkIsValid();

         m_entityManager->remove<C>(m_id);
      }


      bool operator==(const ComponentHandle<C>& other) const
      {
         return m_entityManager == other.m_entityManager && m_id == other.m_id;
      }

      bool operator!=(const ComponentHandle<C>& other) const
      {
         return !(*this == other);
      }

   private:
      friend class EntityManager;

      ComponentHandle(EM* entityManager, Entity::Id id)
         : m_entityManager(entityManager), m_id(id) {}

      void checkIsValid() const
      {
         if (m_entityManager == nullptr)
            throw InvalidComponentError("Entity manager is null.");

         m_entityManager->checkIsValid(m_id);

         if (!m_entityManager->hasComponent<C>(m_id))
            throw InvalidComponentError();
      }

   private:
      EM* m_entityManager;
      Entity::Id m_id;
   };
}