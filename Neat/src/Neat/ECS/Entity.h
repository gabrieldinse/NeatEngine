#pragma once

#include <type_traits>
#include <tuple>
#include <ostream>
#include <bitset>

#include "Neat/Core/Log.h"
#include "Neat/Core/Types.h"
#include "Neat/ECS/Config.h"


namespace Neat
{
   class EntityManager;

   template <typename C, typename EM = EntityManager>
   class ComponentHandle;


   struct Entity
   {
   public:
      class Id
      { 
      public:
         Id() : m_id(0) {}
         explicit Id(UIntLong id) : m_id(id) {}
         Id(UInt index, UInt version)
            : m_id(UIntLong(index) | UIntLong(version) << UIntLong(32)) {}

         UIntLong id() const { return m_id; }
         UInt index() const { return m_id & NT_UINT_MAX; }
         UInt version() const { return m_id >> 32; }

         bool operator==(const Id &other) const { return m_id == other.m_id; }
         bool operator!=(const Id &other) const { return m_id != other.m_id; }
         bool operator<(const Id &other) const { return m_id < other.m_id; }

      private:
         friend class EntityManager;
         UIntLong m_id;
      };

      static const Id INVALID_ID;

   public:
      Entity() = default;
      Entity(EntityManager* manager, Id id) : m_entityManager(manager), m_id(id) {}
      Entity(const Entity& entity) = default;

      Entity& operator=(const Entity& entity);

      explicit operator bool() const;

      bool operator==(const Entity &other) const;
      bool operator!=(const Entity &other) const;
      bool operator<(const Entity &other) const;

      Id id() const;

      bool isValid() const;
      void invalidate();

      template <typename C, typename... Args>
      ComponentHandle<C> add(Args&&... args);

      template <typename C, typename... Args>
      ComponentHandle<C> addFromCopy(const C& component);

      template <typename C, typename... Args>
      ComponentHandle<C> replace(Args&&... args);

      template <typename C>
      void remove();

      template <
         typename C,
         typename = typename std::enable_if<!std::is_const<C>::value>::type>
      ComponentHandle<C> getComponent();

      template <
         typename C,
         typename = typename std::enable_if<std::is_const<C>::value>::type>
      const ComponentHandle<C, const EntityManager> getComponent() const;

      template <typename... Components>
      std::tuple<ComponentHandle<Components>...>  getComponents();

      template <typename... Components>
      std::tuple<ComponentHandle<const Components, const EntityManager>...>
      getComponents() const;

      template <typename C>
      bool hasComponent() const;

      template<typename C1, typename... OtherComponents>
      void unpack(ComponentHandle<C1>& c1,
         ComponentHandle<OtherComponents>&... others);

      void destroy();

      std::bitset<NT_MAX_COMPONENTS> getComponentMask() const;

   private:
      bool checkIsValid() const;

   private:
      EntityManager* m_entityManager = nullptr;
      Id m_id = INVALID_ID;
   };


   std::ostream& operator<<(std::ostream& os, const Entity& entity)
   {
      return os << "Entity(" << entity.id() << ")";
   }

   std::ostream& operator<<(std::ostream& os, const Entity::Id& id)
   {
      return os << "Entity::Id(" << id.index() << "." << id.version() << ")";
   }
}