#include "Neat/Core/Exceptions.h"
#include "Neat/ECS/Entity.h"
#include "Neat/ECS/EntityManager.h"
#include "Neat/ECS/ComponentHandle.h"


namespace Neat
{
   const Entity::Id Entity::INVALID_ID;

   Entity::Entity() = default;
   Entity::Entity(EntityManager* manager, Id id)
      : m_entityManager(manager), m_id(id) {}
   Entity::Entity(const Entity& entity) = default;


   Entity& Entity::operator=(const Entity& entity) = default;


   explicit Entity::operator bool() const { return isValid(); }


   bool Entity::operator==(const Entity &other) const
   {
      return other.m_entityManager == m_entityManager && other.m_id == m_id;
   }

   bool Entity::operator!=(const Entity &other) const
   {
      return !(other == *this);
   }

   bool Entity::operator<(const Entity &other) const
   {
      return other.m_id < m_id;
   }

   bool Entity::isValid() const
   {
      return m_entityManager != nullptr && m_entityManager->isValid(m_id);
   }


   bool Entity::checkIsValid() const
   {
      if (m_entityManager == nullptr)
         throw InvalidEntityError("Entity manager is null.");

      m_entityManager->checkIsValid(m_id);
   }

   void Entity::invalidate()
   {
      m_id = INVALID_ID;
      m_entityManager = nullptr;
   }

   Entity::Id Entity::id() const { return m_id; }


   template <typename C, typename... Args>
   ComponentHandle<C> Entity::add(Args&&... args)
   {
      checkIsValid();

      return m_entityManager->add<C>(m_id, std::forward<Args>(args)...);
   }

   template <typename C, typename... Args>
   ComponentHandle<C> Entity::addFromCopy(const C& component)
   {
      checkIsValid();

      return m_entityManager->add<C>(m_id, std::forward<const C&>(component));
   }

   template <typename C, typename... Args>
   ComponentHandle<C> Entity::replace(Args&&... args)
   {
      checkIsValid();

      auto component_handle = getComponent<C>();
      if (component_handle)
         *(component_handle.get()) = C(std::forward<Args>(args)...);
      else // Does not exist -> add new component to entity
         component_handle = m_entityManager->add<C>(
            m_id, std::forward<Args>(args)...);

      return component_handle;
   }

   template <typename C>
   void Entity::remove()
   {
      NT_CORE_ASSERT(checkIsValid() && hasComponent<C>());
      m_entityManager->remove<C>(m_id);
   }
      
   template <typename C, typename>
   ComponentHandle<C> Entity::getComponent()
   {
      checkIsValid();

      return m_entityManager->getComponent<C>(m_id);
   }

   template <typename C, typename>
   const ComponentHandle<C, const EntityManager> Entity::getComponent() const
   {
      checkIsValid();

      return
         const_cast<const EntityManager*>(
            m_entityManager)->getComponent<const C>(m_id);
   }

   template <typename... Components>
   std::tuple<ComponentHandle<Components>...> Entity::getComponents()
   {
      checkIsValid();

      return m_entityManager->getComponents<Components...>(m_id);
   }

   template <typename... Components>
   std::tuple<ComponentHandle<const Components, const EntityManager>...>
   Entity::getComponents() const
   {
      checkIsValid();

      return
         const_cast<const EntityManager*>(
            m_entityManager)->getComponents<const Components...>(m_id);
   }

   template <typename C>
   bool Entity::hasComponent() const
   {
      checkIsValid();

      return m_entityManager->hasComponent<C>(m_id);
   }

   template<typename C1, typename... OtherComponents>
   void Entity::unpack(ComponentHandle<C1>& c1,
      ComponentHandle<OtherComponents>&... others)
   {
      checkIsValid();

      m_entityManager->unpack(m_id, c1, others...);
   }

   void Entity::destroy()
   {
      checkIsValid();

      m_entityManager->destroy(m_id);
      invalidate();
   }

   std::bitset<NT_MAX_COMPONENTS> Entity::getComponentMask() const
   {
      return m_entityManager->getComponentMask(m_id);
   }
}