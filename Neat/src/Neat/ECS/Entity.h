#pragma once

#include <type_traits>
#include <ostream>
#include <algorithm>
#include <iterator>
#include <bitset>
#include <tuple>
#include <queue>
#include <vector>
#include <string>

#include "Neat/Core/Log.h"
#include "Neat/Core/Types.h"
#include "Neat/ECS/Component.h"
#include "Neat/Events/Event.h"
#include "Neat/Events/EventManager.h"
#include "Neat/Helper/NonCopyable.h"
#include "Neat/Helper/MemoryPool.h"


namespace Neat
{
   class EntityManager;

   template <typename C, typename EM = EntityManager>
   class ComponentHandle;

   using ComponentMask = std::bitset<NT_MAX_COMPONENTS>;


   // ---------------------------------------------------------------------- //
   // Entity --------------------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class Entity
   {
   public:
      // Id ---------------------------------------------------------------- //
      class Id
      { 
      public:
         Id() : m_id(0) {}
         Id(UInt index, UInt version)
            : m_id(UIntLong(index) | UIntLong(version) << 32) {}
         explicit Id(UIntLong id) : m_id(id) {}
         

         UIntLong id() const { return m_id; }
         UInt index() const { return (UInt)(m_id & UIntLong(NT_UINT_MAX)); }
         UInt version() const { return (UInt)(m_id >> 32); }

         bool operator==(const Id &other) const { return m_id == other.m_id; }
         bool operator!=(const Id &other) const { return m_id != other.m_id; }
         bool operator<(const Id &other) const { return m_id < other.m_id; }

      private:
         friend class EntityManager;

      private:
         UIntLong m_id;
      };

      static const Id INVALID_ID;
      // ------------------------------------------------------------------- //

   public:
      Entity() = default;
      Entity(EntityManager* entityManager, Id id)
         : m_entityManager(entityManager), m_id(id) {}
      Entity(const Entity& entity) = default;

      Entity& operator=(const Entity& entity) = default;

      explicit operator bool() const { return isValid(); }


      bool operator==(const Entity& other) const
      {
         return other.m_entityManager == m_entityManager && other.m_id == m_id;
      }

      bool operator!=(const Entity& other) const
      {
         return !(other == *this);
      }

      bool operator<(const Entity& other) const
      {
         return other.m_id < m_id;
      }


      Id id() const { return m_id; }


      bool isValid() const;
      void invalidate();

      template <typename C, typename... Args>
      ComponentHandle<C> addComponent(Args&&... args);

      template <typename C, typename... Args>
      ComponentHandle<C> addComponentFromCopy(const C& component);

      template <typename C, typename... Args>
      ComponentHandle<C> replaceComponent(Args&&... args);

      template <typename C>
      void removeComponent();

      template <
         typename C,
         typename = typename std::enable_if_t<!std::is_const<C>::value>>
      ComponentHandle<C> getComponent();

      template <
         typename C,
         typename = typename std::enable_if_t<std::is_const<C>::value>>
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

      ComponentMask getComponentMask() const;

   private:
      void checkIsValid() const;

   private:
      EntityManager* m_entityManager = nullptr;
      Id m_id = INVALID_ID;
   };

   std::ostream& operator<<(std::ostream& os, const Entity& entity);
   std::ostream& operator<<(std::ostream& os, const Entity::Id& id);


   // ---------------------------------------------------------------------- //
   // ComponentHandle ------------------------------------------------------ //
   // ---------------------------------------------------------------------- //
   template <typename C, typename EM>
   class ComponentHandle
   {
   public:
      ComponentHandle() : m_entityManager(nullptr) {}

      explicit operator bool() const;
      bool isValid() const;

      C* operator->();
      const C* operator->() const;
      C* get();
      const C* get() const;

      void remove();


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

      void checkIsValid() const;

   private:
      EM* m_entityManager;
      Entity::Id m_id;
   };


   // ---------------------------------------------------------------------- //
   // ECS events ----------------------------------------------------------- //
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
   class EntityManager : public NonCopyable
   {
   public:
      explicit EntityManager(EventManager& eventManager);
      virtual ~EntityManager();

   public:
      // ViewIterator ---------------------------------------------------------
      template <class DelegatedIterator, bool IterateOverAll = false>
      class ViewIterator
      {
      public:
         using iterator_category = std::input_iterator_tag;
         using value_type = Entity::Id;
         using difference_type = std::ptrdiff_t;
         using pointer = value_type*;
         using reference = value_type&;

      public:
         DelegatedIterator& operator++()
         {
            ++m_pos;
            next();

            return *static_cast<DelegatedIterator*>(this);
         }

         Entity operator*()
         {
            return Entity(m_entityManager, m_entityManager->createId(m_pos));
         }

         const Entity operator*() const
         {
            return Entity(m_entityManager, m_entityManager->createId(m_pos));
         }


         bool operator==(const DelegatedIterator& rhs) const
         {
            return m_pos == rhs.m_pos;
         }

         bool operator!=(const DelegatedIterator& rhs) const
         {
            return m_pos != rhs.m_pos;
         }
         
      protected:
         ViewIterator(EntityManager* entityManager, UInt index)
            : m_entityManager(entityManager)
            , m_pos(index)
            , m_capacity(m_entityManager->capacity())
            , m_freeCursor(NT_UINT_MAX)
         {
            if (IterateOverAll)
            {
               std::sort(
                  m_entityManager->m_freeEntityIds.begin(),
                  m_entityManager->m_freeEntityIds.end());
               m_freeCursor = 0;
            }
         }

         ViewIterator(EntityManager* entityManager,
            const ComponentMask componentGroupMask,
            UInt index)
            : m_entityManager(entityManager)
            , m_componentGroupMask(componentGroupMask)
            , m_pos(index)
            , m_capacity(m_entityManager->capacity())
            , m_freeCursor(NT_UINT_MAX)
         {
            if (IterateOverAll)
            {
               std::sort(
                  m_entityManager->m_freeEntityIds.begin(),
                  m_entityManager->m_freeEntityIds.end());
               m_freeCursor = 0;
            }
         }


         void next()
         { 
            while (m_pos < m_capacity &&
               !((IterateOverAll && IsValidEntity()) || matchComponentMask()))
            {
               ++m_pos;
            }

            if (m_pos < m_capacity)
            {
               Entity entity = m_entityManager->getEntity(
                  m_entityManager->createId(m_pos));
               static_cast<DelegatedIterator*>(this)->nextEntity(entity);
            }
         }

         bool matchComponentMask() const
         {
            return
               (m_entityManager->m_entityComponentMasks[m_pos] & m_componentGroupMask)
               == m_componentGroupMask;
         }

         bool IsValidEntity()
         {
            if (m_freeCursor < m_entityManager->m_freeEntityIds.size() &&
               m_entityManager->m_freeEntityIds[m_freeCursor] == m_pos)
            {
               ++m_freeCursor;
               return false;
            }

            return true;
         }
         
      protected:
         EntityManager* m_entityManager;
         ComponentMask m_componentGroupMask;
         UInt m_pos;
         std::size_t m_capacity;
         std::size_t m_freeCursor;
      };
      // ----------------------------------------------------------------------


      // BaseView -------------------------------------------------------------
      template <bool IterateOverAll>
      class BaseView
      {
      public:
         // Iterator ----------------------------------------------------------
         class Iterator : public ViewIterator<Iterator, IterateOverAll>
         {
         public:
            Iterator(EntityManager* entityManager,
               const ComponentMask componentGroupMask, UInt index)
               : ViewIterator<Iterator, IterateOverAll>(
                  entityManager, componentGroupMask, index)
            {
               ViewIterator<Iterator, IterateOverAll>::next();
            }

            void nextEntity(Entity& entity) {}
         };
         // -------------------------------------------------------------------

      public:
         Iterator begin()
         {
            return Iterator(m_entityManager, m_componentGroupMask, 0);
         }

         Iterator end()
         {
            return
               Iterator(m_entityManager, m_componentGroupMask,
                  (UInt)m_entityManager->capacity());
         }

         const Iterator begin() const
         {
            return Iterator(m_entityManager, m_componentGroupMask, 0);
         }

         const Iterator end() const
         {
            return
               Iterator(m_entityManager, m_componentGroupMask,
                  (UInt)m_entityManager->capacity());
         }

      private:
         friend class EntityManager;

         explicit BaseView(EntityManager* entityManager)
            : m_entityManager(entityManager)
         {
            m_componentGroupMask.set();
         }

         BaseView(EntityManager* entityManager,
            ComponentMask componentGroupMask)
            : m_entityManager(entityManager)
            , m_componentGroupMask(componentGroupMask) {}

      private:
         EntityManager* m_entityManager;
         ComponentMask m_componentGroupMask;
      };

      using View = BaseView<false>;
      using DebugView = BaseView<true>;
      // ----------------------------------------------------------------------


      // UnpackingView --------------------------------------------------------
      template <typename... Components>
      class UnpackingView
      {
      public:
         // Unpacker ----------------------------------------------------------
         class Unpacker
         {
         public:
            explicit Unpacker(ComponentHandle<Components>&... componentHandles)
               : m_componentHandles(
                  std::tuple<ComponentHandle<Components>&...>(handles...)) {}

            void unpack(Entity& entity) const
            {
               unpackNComponents<0, Components...>(entity);
            }

         private:
            template <std::size_t N, typename C>
            void unpackNComponents(Entity& entity) const
            {
               std::get<N>(m_componentHandles) = entity.getComponent<C>();
            }

            template <std::size_t N, typename C1, typename C2, typename... Cn>
            void unpackNComponents(Entity& entity) const
            {
               std::get<N>(m_componentHandles) = entity.getComponent<C1>();
               unpackNComponents<N + 1, C2, Cn...>(entity);
            }

         private:
            std::tuple<ComponentHandle<Components>&...> m_componentHandles;
         };
         // -------------------------------------------------------------------

         // Iterator ----------------------------------------------------------
         class Iterator : public ViewIterator<Iterator>
         {
         public:
            Iterator(EntityManager* entityManager,
               const ComponentMask componentGroupMask,
               Int index, const Unpacker& unpacker)
               : ViewIterator<Iterator>(entityManager, componentGroupMask,
                  index)
               , m_unpacker(unpacker)
            {
               ViewIterator<Iterator>::next();
            }

            void nextEntity(Entity& entity)
            {
               m_unpacker.unpack(entity);
            }

         private:
            const Unpacker& m_unpacker;
         };
         // -------------------------------------------------------------------

      public:
         Iterator begin()
         {
            return Iterator(m_entityManager, m_componentGroupMask, 0,
               m_unpacker);
         }

         Iterator end()
         {
            return
               Iterator(m_entityManager, m_componentGroupMask,
                  m_entityManager->capacity(), m_unpacker);
         }

         const Iterator begin() const
         {
            return Iterator(m_entityManager, m_componentGroupMask, 0,
               m_unpacker);
         }

         const Iterator end() const
         {
            return
               Iterator(m_entityManager, m_componentGroupMask,
                  m_entityManager->capacity(), m_unpacker);
         }

      private:
         friend class EntityManager;

         UnpackingView(EntityManager* entityManager,
            ComponentMask componentGroupMask,
            ComponentHandle<Components>&... handles)
            : m_entityManager(entityManager)
            , m_componentGroupMask(componentGroupMask)
            , m_unpacker(handles...) {}

      private:
         EntityManager* m_entityManager;
         ComponentMask m_componentGroupMask;
         Unpacker m_unpacker;
      };
      // ----------------------------------------------------------------------

   public:
      std::size_t size() const
      {
         return m_entityComponentMasks.size() - m_freeEntityIds.size();
      }

      std::size_t capacity() const
      {
         return m_entityComponentMasks.size();
      }


      void reset();


      bool isValid(Entity::Id id)
      {
         return
            id.index() < m_entityIdsVersion.size() &&
            m_entityIdsVersion[id.index()] == id.version();
      }


      Entity createEntity()
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
            index = m_freeEntityIds.back();
            m_freeEntityIds.pop_back();
            version = m_entityIdsVersion[index];
         }

         Entity entity(this, Entity::Id(index, version));
         m_eventManager.publish<EntityCreatedEvent>(entity);

         return entity;
      }

      void destroyEntity(Entity::Id id)
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
         m_freeEntityIds.push_back(index);
      }


      Entity getEntity(Entity::Id id)
      {
         checkIsValid(id);

         return Entity(this, id);
      }

      Entity::Id createId(UInt index) const
      {
         return Entity::Id(index, m_entityIdsVersion[index]);
      }


      template <typename C, typename... Args>
      ComponentHandle<C> addComponent(Entity::Id id, Args&&... args)
      {
         checkIsValid(id);

         const BaseComponent::Family family = getComponentFamily<C>();
         UInt index = id.index();

         if (m_entityComponentMasks[index].test(family))
            throw ComponentAlreadyAddedError();

         MemoryPool<C>* component_array = accomodateComponent<C>();
         new (component_array->at(index)) C(std::forward<Args>(args)...);

         m_entityComponentMasks[index].set(family);

         ComponentHandle<C> component(this, id);
         m_eventManager.publish<ComponentAddedEvent<C>>(
            Entity(this, id), component);

         return component;
      }

      template <typename C>
      void removeComponent(Entity::Id id)
      {
         checkIsValid(id);

         const BaseComponent::Family family = getComponentFamily<C>();

         BaseMemoryPool* component_array = m_componentArrays[family];
         ComponentHandle<C> component(this, id);
         m_eventManager.publish<ComponentRemovedEvent<C>>(
            Entity(this, id), component);

         m_entityComponentMasks[id.index()].reset(family);

         component_array->destroy(id.index());
      }

      template <typename C>
      bool hasComponent(Entity::Id id) const
      {
         checkIsValid(id);

         std::size_t family = getComponentFamily<C>();

         if (family >= m_componentArrays.size())
            return false;

         BaseMemoryPool* component_array = m_componentArrays[family];

         if (component_array == nullptr || 
            m_entityComponentMasks[id.index()][family] == nullptr)
            return false;

         return true;
      }

      template <
         typename C,
         typename std::enable_if_t<!std::is_const<C>::value>
      >
      ComponentHandle<C> getComponent(Entity::Id id)
      {
         checkIsValid(id);

         if (!hasComponent<C>())
            return ComponentHandle<C>();

         return ComponentHandle<C>(this, id);
      }

      template <
         typename C, 
         typename std::enable_if_t<std::is_const<C>::value>
      >
      const ComponentHandle<C, const EntityManager> getComponent(
         Entity::Id id) const
      {
         checkIsValid(id);

         if (!hasComponent<C>())
            return ComponentHandle<C, const EntityManager>();

         return ComponentHandle<C, const EntityManager>(this, id);
      }

      template <typename... Components>
      std::tuple<ComponentHandle<Components>...> getComponents(Entity::Id id)
      {
         return std::make_tuple(getComponent<Components>(id)...);
      }

      template <typename... Components>
      std::tuple<ComponentHandle<const Components, const EntityManager>...>
      getComponents(Entity::Id id) const
      {
         return std::make_tuple(getComponent<const Components>(id)...);
      }


      template <typename... Components>
      View entitiesWithComponents()
      {
         auto component_mask = createComponentMask<Components...>();

         return View(this, component_mask);
      }

      template <typename... Components>
      UnpackingView<Components...> entitiesWithComponents(
         ComponentHandle<Components>&... components)
      {
         auto component_mask = createComponentMask<Components...>();

         return UnpackingView<Components...>(this, component_mask);
      }

      DebugView entitiesForDebugging()
      {
         return DebugView(this);
      }

      
      template <typename C>
      void unpack(Entity::Id id, ComponentHandle<C>& component)
      {
         checkIsValid(id);
         component = getComponent<C>(id);
      }

      template <typename C1, typename... Cn>
      void unpack(Entity::Id id, ComponentHandle<C1>& component,
         ComponentHandle<Cn>&... others)
      {
         checkIsValid(id);

         component = getComponent<C1>(id);
         unpack<Cn...>(id, others...);
      }


      template <typename C>
      static BaseComponent::Family getComponentFamily()
      {
         return Component<typename std::remove_const_t<C>>::getFamily();
      }


   private:
      friend class Entity;

      template <typename C, typename EM>
      friend class ComponentHandle;


      void checkIsValid(Entity::Id id)
      {
         if (id.index() >= m_entityIdsVersion.size())
            throw InvalidEntityIdIndexError();

         if (m_entityIdsVersion[id.index()] != id.version())
            throw InvalidEntityIdVersionError();
      }


      template <typename C>
      C* getComponentPtr(Entity::Id id)
      {
         checkIsValid(id);

         BaseMemoryPool* component_array =
            m_componentArrays[getComponentFamily<C>()];

         NT_CORE_ASSERT(component_array != nullptr,
            "Entity does not have this component.");

         return static_cast<C*>(component_array->at(id.index()));
      }

      template <typename C>
      const C* getComponentPtr(Entity::Id id) const
      {
         checkIsValid(id);

         BaseMemoryPool* component_array =
            m_componentArrays[getComponentFamily<C>()];

         NT_CORE_ASSERT(component_array != nullptr,
            "Entity does not have this component.");

         return static_cast<const C*>(component_array->at(id.index()));
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

      template <typename C1, typename C2, typename... Cn>
      ComponentMask createComponentMask()
      {
         return
            createComponentMask<C1>() | createComponentMask<C2, Cn...>();
      }

      template <typename C>
      ComponentMask createComponentMask(
         const ComponentHandle<C>& componentHandle)
      {
         return createComponentMask<C>();
      }

      template <typename C1, typename... Cn>
      ComponentMask createComponentMask(
         const ComponentHandle<C1>& componentHandle1,
         const ComponentHandle<Cn>&... others)
      {
         return createComponentMask<C1, Cn...>();
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
            MemoryPool<C>* component_array = new MemoryPool<C>();
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
      std::vector<UInt> m_freeEntityIds;
   };
   // ---------------------------------------------------------------------- //
   // ---------------------------------------------------------------------- //



   // ---------------------------------------------------------------------- //
   // Methods definitions -------------------------------------------------- //
   // ---------------------------------------------------------------------- //

   // Entity methods ------------------------------------------------------- //
   inline
   bool Entity::isValid() const
   {
      return m_entityManager != nullptr && m_entityManager->isValid(m_id);
   }

   inline
   void Entity::checkIsValid() const
   {
      if (m_entityManager == nullptr)
         throw InvalidEntityError("Assigned EntityManager is null.");

      m_entityManager->checkIsValid(m_id);
   }

   inline
   void Entity::invalidate()
   {
      m_id = INVALID_ID;
      m_entityManager = nullptr;
   }


   template <typename C, typename... Args>
   inline
   ComponentHandle<C> Entity::addComponent(Args&&... args)
   {
      checkIsValid();

      return m_entityManager->addComponent<C>(m_id, std::forward<Args>(args)...);
   }

   template <typename C, typename... Args>
   inline
   ComponentHandle<C> Entity::addComponentFromCopy(const C& component)
   {
      checkIsValid();

      return m_entityManager->addComponent<C>(m_id, std::forward<const C&>(component));
   }

   template <typename C, typename... Args>
   inline
   ComponentHandle<C> Entity::replaceComponent(Args&&... args)
   {
      checkIsValid();

      auto component_handle = getComponent<C>();
      if (component_handle)
         *(component_handle.get()) = C(std::forward<Args>(args)...);
      else // Does not exist -> add new component to entity
         component_handle = m_entityManager->addComponent<C>(
            m_id, std::forward<Args>(args)...);

      return component_handle;
   }

   template <typename C>
   inline
   void Entity::removeComponent()
   {
      checkIsValid();

      if (!hasComponent<C>())
         throw ComponentNotPresentError();

      m_entityManager->removeComponent<C>(m_id);
   }
      
   template <typename C, typename>
   inline
   ComponentHandle<C> Entity::getComponent()
   {
      checkIsValid();

      return m_entityManager->getComponent<C>(m_id);
   }

   template <typename C, typename>
   inline
   const ComponentHandle<C, const EntityManager> Entity::getComponent() const
   {
      checkIsValid();

      return
         const_cast<const EntityManager*>(
            m_entityManager)->getComponent<const C>(m_id);
   }

   template <typename... Components>
   inline
   std::tuple<ComponentHandle<Components>...> Entity::getComponents()
   {
      checkIsValid();

      return m_entityManager->getComponents<Components...>(m_id);
   }

   template <typename... Components>
   inline
   std::tuple<ComponentHandle<const Components, const EntityManager>...>
   Entity::getComponents() const
   {
      checkIsValid();

      return
         const_cast<const EntityManager*>(
            m_entityManager)->getComponents<const Components...>(m_id);
   }

   template <typename C>
   inline
   bool Entity::hasComponent() const
   {
      checkIsValid();

      return m_entityManager->hasComponent<C>(m_id);
   }


   template<typename C1, typename... OtherComponents>
   inline
   void Entity::unpack(ComponentHandle<C1>& c1,
      ComponentHandle<OtherComponents>&... others)
   {
      checkIsValid();

      m_entityManager->unpack(m_id, c1, others...);
   }


   inline
   void Entity::destroy()
   {
      checkIsValid();

      m_entityManager->destroyEntity(m_id);
      invalidate();
   }


   inline
   std::bitset<NT_MAX_COMPONENTS> Entity::getComponentMask() const
   {
      return m_entityManager->getComponentMask(m_id);
   }
   // ---------------------------------------------------------------------- //


   template<typename C, typename EM>
   inline ComponentHandle<C, EM>::operator bool() const
   {
      return isValid();
   }

   // ComponentHandle methods ---------------------------------------------- //
   template <typename C, typename EM>
   inline
   bool ComponentHandle<C, EM>::isValid() const
   {
      return
         m_entityManager != nullptr &&
         !m_entityManager->isValid(m_id) &&
         m_entityManager->hasComponent<C>(m_id);
   }

   template <typename C, typename EM>
   inline
   void ComponentHandle<C, EM>::checkIsValid() const
   {
      if (m_entityManager == nullptr)
         throw InvalidComponentError("Assigned EntityManager is null.");

      try
      {
         m_entityManager->checkIsValid(m_id);
      }
      catch (const EntityError& e)
      {
         throw InvalidComponentError(
            "Assigned Entity is invalid.\n" + e.what());
      }

      if (!m_entityManager->hasComponent<C>(m_id))
         throw InvalidComponentError();
   }


   template <typename C, typename EM>
   inline
   C* ComponentHandle<C, EM>::operator->()
   {
      checkIsValid();

      return m_entityManager->getComponentPtr<C>(m_id);
   }

   template <typename C, typename EM>
   inline
   const C* ComponentHandle<C, EM>::operator->() const
   {
      checkIsValid();

      return m_entityManager->getComponentPtr<C>(m_id);
   }

   template <typename C, typename EM>
   inline
   C* ComponentHandle<C, EM>::get()
   {
      checkIsValid();

      return m_entityManager->getComponentPtr<C>(m_id);
   }

   template <typename C, typename EM>
   inline
   const C* ComponentHandle<C, EM>::get() const
   {
      checkIsValid();

      return m_entityManager->getComponentPtr<C>(m_id);
   }


   template <typename C, typename EM>
   inline
   void ComponentHandle<C, EM>::remove()
   {
      checkIsValid();

      m_entityManager->remove<C>(m_id);
   }
   // ---------------------------------------------------------------------- //



}