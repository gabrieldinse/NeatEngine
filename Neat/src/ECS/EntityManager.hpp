#pragma once

#include <algorithm>
#include <bitset>
#include <iterator>
#include <ostream>
#include <tuple>
#include <type_traits>
#include <vector>
#include <optional>

#include "Component.hpp"

#include "Core/Limits.hpp"
#include "Core/Assert.hpp"
#include "Core/Types.hpp"
#include "EventDispatching/EventDispatcher.hpp"
#include "Utils/MemoryPool.hpp"
#include "Utils/NonCopyable.hpp"

namespace Neat {
class EntityManager;

template <typename C, typename EM = EntityManager>
class ComponentHandle;

using ComponentMask = std::bitset<MaxComponents>;

// ---------------------------------------------------------------------- //
// Entity --------------------------------------------------------------- //
// ---------------------------------------------------------------------- //
class Entity {
 public:
  // ID ---------------------------------------------------------------- //
  class ID {
   public:
    constexpr ID() : m_id(0) {}
    constexpr ID(UInt32 index, UInt32 version)
        : m_id(static_cast<UInt64>(version) << 32 |
               static_cast<UInt64>(index)) {}
    explicit constexpr ID(UInt64 id) : m_id(id) {}

    [[nodiscard]] UInt64 id() const { return m_id; }
    [[nodiscard]] UInt32 index() const {
      return static_cast<UInt32>(m_id & UINT64_C(0xFFFFFFFF));
    }
    [[nodiscard]] UInt32 version() const {
      return static_cast<UInt32>(m_id >> 32);
    }

    [[nodiscard]] explicit operator UInt64() const { return m_id; }

    [[nodiscard]] bool operator==(const ID &other) const {
      return m_id == other.m_id;
    }
    [[nodiscard]] bool operator==(UInt64 other) const { return m_id == other; }
    [[nodiscard]] bool operator!=(const ID &other) const {
      return m_id != other.m_id;
    }
    [[nodiscard]] bool operator<(const ID &other) const {
      return m_id < other.m_id;
    }

    static constexpr UInt32 InvalidIndex{Limits::Max<UInt32>};
    static constexpr UInt32 InvalidVersion{Limits::Max<UInt32>};

   private:
    friend class EntityManager;

   private:
    UInt64 m_id;
  };

  static const ID InvalidID;
  // ------------------------------------------------------------------- //

 public:
  Entity() = default;
  Entity(EntityManager *entityManager, ID id)
      : m_entityManager(entityManager), m_id(id) {}
  Entity(const Entity &entity) = default;

  Entity &operator=(const Entity &entity) = default;

  [[nodiscard]] explicit operator bool() const { return isValid(); }
  [[nodiscard]] explicit operator UInt64() const { return m_id.id(); }

  [[nodiscard]] bool operator==(const Entity &other) const {
    return other.m_entityManager == m_entityManager and other.m_id == m_id;
  }
  [[nodiscard]] bool operator!=(const Entity &other) const {
    return not(other == *this);
  }
  [[nodiscard]] bool operator<(const Entity &other) const {
    return m_id < other.m_id;
  }

  [[nodiscard]] ID id() const { return m_id; }

  [[nodiscard]] bool isValid() const;
  void invalidate();

  template <typename C, typename... Args>
  std::optional<ComponentHandle<C>> addComponent(Args &&...args);

  template <typename C, typename... Args>
  std::optional<ComponentHandle<C>> addComponentFromCopy(const C &component);

  template <typename C, typename... Args>
  std::optional<ComponentHandle<C>> replaceComponent(Args &&...args);

  template <typename C>
  bool removeComponent();

  template <typename C>
  [[nodiscard]] std::optional<ComponentHandle<C>> getComponent();

  template <typename C>
  [[nodiscard]] std::optional<const ComponentHandle<C, const EntityManager>>
  getComponent() const;

  template <typename... Components>
  [[nodiscard]] std::tuple<std::optional<ComponentHandle<Components>>...>
  getComponents();

  template <typename... Components>
  [[nodiscard]] std::tuple<
      std::optional<ComponentHandle<const Components, const EntityManager>>...>
  getComponents() const;

  template <typename C>
  [[nodiscard]] bool hasComponent() const;

  [[nodiscard]] bool hasComponent(BaseComponent::Family family) const;

  [[nodiscard]] bool hasAnyComponent() const;

  template <typename C1, typename... OtherComponents>
  bool unpack(ComponentHandle<C1> &c1,
              ComponentHandle<OtherComponents> &...others);

  bool destroy();

  [[nodiscard]] std::optional<ComponentMask> getComponentMask() const;

 private:
  EntityManager *m_entityManager{nullptr};
  ID m_id{InvalidID};
};

std::ostream &operator<<(std::ostream &os, const Entity &entity);
std::ostream &operator<<(std::ostream &os, const Entity::ID &id);

// ---------------------------------------------------------------------- //
// ComponentHandle ------------------------------------------------------ //
// ---------------------------------------------------------------------- //
template <typename C, typename EM>
class ComponentHandle {
 public:
  ComponentHandle() : m_entityManager(nullptr) {}

  [[nodiscard]] explicit operator bool() const;
  [[nodiscard]] bool isValid() const;

  [[nodiscard]] C *operator->();
  [[nodiscard]] const C *operator->() const;
  [[nodiscard]] C *get();
  [[nodiscard]] const C *get() const;
  [[nodiscard]] C &operator*() { return *get(); }
  [[nodiscard]] const C &operator*() const { return *get(); }

  bool remove();

  [[nodiscard]] bool operator==(const ComponentHandle<C> &other) const {
    return m_entityManager == other.m_entityManager and m_id == other.m_id;
  }

  [[nodiscard]] bool operator!=(const ComponentHandle<C> &other) const {
    return not(*this == other);
  }

 private:
  friend class EntityManager;

  ComponentHandle(EM *entityManager, const Entity::ID &id)
      : m_entityManager(entityManager), m_id(id) {}

 private:
  EM *m_entityManager;
  Entity::ID m_id;
};

// ---------------------------------------------------------------------- //
// ECS events ----------------------------------------------------------- //
// ---------------------------------------------------------------------- //
struct EntityCreatedEvent {
  explicit EntityCreatedEvent(const Entity &entity) : entity(entity) {}
  virtual ~EntityCreatedEvent() {}

  Entity entity;
};

struct EntityDestroyedEvent {
  explicit EntityDestroyedEvent(const Entity &entity) : entity(entity) {}
  virtual ~EntityDestroyedEvent() {}

  Entity entity;
};

template <typename C>
struct ComponentAddedEvent {
  ComponentAddedEvent(const Entity &entity, const C &component)
      : entity(entity), component(component) {}

  Entity entity;
  C component;
};

template <typename C>
struct ComponentRemovedEvent {
  ComponentRemovedEvent(const Entity &entity, const C &component)
      : entity(entity), component(component) {}

  Entity entity;
  C component;
};

// ---------------------------------------------------------------------- //
// EntityManager -------------------------------------------------------- //
// ---------------------------------------------------------------------- //
class EntityManager : public NonCopyable {
 public:
  explicit EntityManager(const Ref<EventDispatcher> &eventDispatcher);
  virtual ~EntityManager();

 public:
  // ViewIterator ---------------------------------------------------------
  template <class DelegatedIterator, bool IterateOverAll = false>
  class ViewIterator {
   public:
    using IteratorCategory = std::input_iterator_tag;
    using ValueType = Entity::ID;
    using DifferenceType = std::ptrdiff_t;
    using Pointer = ValueType *;
    using Reference = ValueType &;

   public:
    DelegatedIterator &operator++() {
      ++m_pos;
      next();

      return *static_cast<DelegatedIterator *>(this);
    }

    [[nodiscard]] Entity operator*() {
      return Entity(m_entityManager, m_entityManager->createId(m_pos));
    }

    [[nodiscard]] const Entity operator*() const {
      return Entity(m_entityManager, m_entityManager->createId(m_pos));
    }

    [[nodiscard]] bool operator==(const DelegatedIterator &rhs) const {
      return m_pos == rhs.m_pos;
    }

    [[nodiscard]] bool operator!=(const DelegatedIterator &rhs) const {
      return m_pos != rhs.m_pos;
    }

   protected:
    ViewIterator(EntityManager *entityManager, UInt32 index)
        : m_entityManager(entityManager),
          m_pos(index),
          m_capacity(m_entityManager->capacity()),
          m_freeCursor(Limits::Max<UInt32>) {
      if (IterateOverAll) {
        std::sort(m_entityManager->m_freeEntityIds.begin(),
                  m_entityManager->m_freeEntityIds.end());
        m_freeCursor = 0;
      }
    }

    ViewIterator(EntityManager *entityManager,
                 const ComponentMask componentGroupMask, UInt32 index)
        : m_entityManager(entityManager),
          m_componentGroupMask(componentGroupMask),
          m_pos(index),
          m_capacity(m_entityManager->capacity()),
          m_freeCursor(Limits::Max<UInt32>) {
      if (IterateOverAll) {
        std::sort(m_entityManager->m_freeEntityIds.begin(),
                  m_entityManager->m_freeEntityIds.end());
        m_freeCursor = 0;
      }
    }

    void next() {
      while (m_pos < m_capacity and not((IterateOverAll and isValidEntity()) or
                                        matchComponentMask())) {
        ++m_pos;
      }

      if (m_pos < m_capacity) {
        auto entityOpt{
            m_entityManager->getEntity(m_entityManager->createId(m_pos))};
        if (entityOpt) {
          Entity entity{*entityOpt};
          static_cast<DelegatedIterator *>(this)->nextEntity(entity);
        }
      }
    }

    [[nodiscard]] bool matchComponentMask() const {
      return (m_entityManager->m_entityComponentMasks[m_pos] &
              m_componentGroupMask) == m_componentGroupMask;
    }

    [[nodiscard]] bool isValidEntity() {
      if (m_freeCursor < m_entityManager->m_freeEntityIds.size() and
          m_entityManager->m_freeEntityIds[m_freeCursor] == m_pos) {
        ++m_freeCursor;
        return false;
      }

      return true;
    }

   protected:
    EntityManager *m_entityManager;
    ComponentMask m_componentGroupMask;
    UInt32 m_pos;
    std::size_t m_capacity;
    std::size_t m_freeCursor;
  };
  // ----------------------------------------------------------------------

  // BaseView -------------------------------------------------------------
  template <bool IterateOverAll>
  class BaseView {
   public:
    // Iterator ----------------------------------------------------------
    class Iterator : public ViewIterator<Iterator, IterateOverAll> {
     public:
      Iterator(EntityManager *entityManager,
               const ComponentMask componentGroupMask, UInt32 index)
          : ViewIterator<Iterator, IterateOverAll>(entityManager,
                                                   componentGroupMask, index) {
        ViewIterator<Iterator, IterateOverAll>::next();
      }

      void nextEntity([[maybe_unused]] Entity &entity) {}
    };
    // -------------------------------------------------------------------

   public:
    [[nodiscard]] Iterator begin() {
      return Iterator(m_entityManager, m_componentGroupMask, 0);
    }

    [[nodiscard]] Iterator end() {
      return Iterator(m_entityManager, m_componentGroupMask,
                      static_cast<UInt32>(m_entityManager->capacity()));
    }

    [[nodiscard]] const Iterator begin() const {
      return Iterator(m_entityManager, m_componentGroupMask, 0);
    }

    [[nodiscard]] const Iterator end() const {
      return Iterator(m_entityManager, m_componentGroupMask,
                      static_cast<UInt32>(m_entityManager->capacity()));
    }

   private:
    friend class EntityManager;

    explicit BaseView(EntityManager *entityManager)
        : m_entityManager(entityManager) {
      m_componentGroupMask.set();
    }

    BaseView(EntityManager *entityManager, ComponentMask componentGroupMask)
        : m_entityManager(entityManager),
          m_componentGroupMask(componentGroupMask) {}

   private:
    EntityManager *m_entityManager;
    ComponentMask m_componentGroupMask;
  };

  using View = BaseView<false>;
  using DebugView = BaseView<true>;
  // ----------------------------------------------------------------------

  // UnpackingView --------------------------------------------------------
  template <typename... Components>
  class UnpackingView {
   public:
    // Unpacker ----------------------------------------------------------
    class Unpacker {
     public:
      explicit Unpacker(ComponentHandle<Components> &...componentHandles)
          : m_componentHandles(componentHandles...) {}

      void unpack(Entity &entity) const {
        unpackNComponents<0, Components...>(entity);
      }

     private:
      template <std::size_t N, typename C>
      void unpackNComponents(Entity &entity) const {
        auto componentOpt{entity.getComponent<C>()};
        if (componentOpt) {
          std::get<N>(m_componentHandles) = *componentOpt;
        }
      }

      template <std::size_t N, typename C1, typename C2, typename... Cn>
      void unpackNComponents(Entity &entity) const {
        auto componentOpt{entity.getComponent<C1>()};
        if (componentOpt) {
          std::get<N>(m_componentHandles) = *componentOpt;
        }
        unpackNComponents<N + 1, C2, Cn...>(entity);
      }

     private:
      std::tuple<ComponentHandle<Components> &...> m_componentHandles;
    };
    // -------------------------------------------------------------------

    // Iterator ----------------------------------------------------------
    class Iterator : public ViewIterator<Iterator> {
     public:
      Iterator(EntityManager *entityManager,
               const ComponentMask componentGroupMask, UInt32 index,
               const Unpacker &unpacker)
          : ViewIterator<Iterator>(entityManager, componentGroupMask, index),
            m_unpacker(unpacker) {
        ViewIterator<Iterator>::next();
      }

      void nextEntity(Entity &entity) { m_unpacker.unpack(entity); }

     private:
      const Unpacker &m_unpacker;
    };
    // -------------------------------------------------------------------

   public:
    [[nodiscard]] Iterator begin() {
      return Iterator(m_entityManager, m_componentGroupMask, 0, m_unpacker);
    }

    [[nodiscard]] Iterator end() {
      return Iterator(m_entityManager, m_componentGroupMask,
                      static_cast<UInt32>(m_entityManager->capacity()),
                      m_unpacker);
    }

    [[nodiscard]] const Iterator begin() const {
      return Iterator(m_entityManager, m_componentGroupMask, 0, m_unpacker);
    }

    [[nodiscard]] const Iterator end() const {
      return Iterator(m_entityManager, m_componentGroupMask,
                      static_cast<UInt32>(m_entityManager->capacity()),
                      m_unpacker);
    }

   private:
    friend class EntityManager;

    UnpackingView(EntityManager *entityManager,
                  ComponentMask componentGroupMask,
                  ComponentHandle<Components> &...componentHandles)
        : m_entityManager(entityManager),
          m_componentGroupMask(componentGroupMask),
          m_unpacker(componentHandles...) {}

   private:
    EntityManager *m_entityManager;
    ComponentMask m_componentGroupMask;
    Unpacker m_unpacker;
  };
  // ----------------------------------------------------------------------

 public:
  [[nodiscard]] std::size_t size() const {
    return m_entityComponentMasks.size() - m_freeEntityIds.size();
  }

  [[nodiscard]] std::size_t capacity() const {
    return m_entityComponentMasks.size();
  }

  void reset();

  [[nodiscard]] bool hasEntity(const Entity &entity) const {
    return hasEntity(entity.id());
  }

  [[nodiscard]] bool hasEntity(const Entity::ID &id) const {
    return isEntityIndexValid(id) and isEntityVersionValid(id);
  }

  [[nodiscard]] bool isValid(const Entity::ID &id) const {
    return hasEntity(id);
  }

  [[nodiscard]] Entity createEntity() {
    UInt32 index;
    UInt32 version;

    if (m_freeEntityIds.empty()) {
      index = m_indexCounter++;
      accomodateEntity(index);
      version = m_entityIdsVersion[index] = 1;
    } else {
      index = m_freeEntityIds.back();
      m_freeEntityIds.pop_back();
      version = m_entityIdsVersion[index];
    }

    Entity entity(this, Entity::ID(index, version));
    m_eventDispatcher->enqueue<EntityCreatedEvent>(entity);

    return entity;
  }

  bool destroyEntity(const Entity &entity) {
    return destroyEntity(entity.id());
  }

  bool destroyEntity(const Entity::ID &id) {
    if (not isValid(id)) {
      return false;
    }

    UInt32 index{id.index()};
    auto componentMask{m_entityComponentMasks[index]};

    m_eventDispatcher->enqueue<EntityDestroyedEvent>(Entity(this, id));

    for (std::size_t i = 0; i < m_componentMemoryPools.size(); ++i) {
      BaseMemoryPool *componentMemoryPool{m_componentMemoryPools[i]};
      if (componentMemoryPool and componentMask.test(i)) {
        componentMemoryPool->destroy(index);
      }
    }

    m_entityComponentMasks[index].reset();
    ++m_entityIdsVersion[index];
    m_freeEntityIds.push_back(index);
    return true;
  }

  [[nodiscard]] std::optional<Entity> getEntity(const Entity::ID &id) {
    if (not isValid(id)) {
      return std::nullopt;
    }

    return Entity(this, id);
  }

  [[nodiscard]] std::optional<Entity> getEntity(UInt32 index) {
    return getEntity(createId(index));
  }

  [[nodiscard]] Entity::ID createId(UInt32 index) const {
    return Entity::ID(index, m_entityIdsVersion[index]);
  }

  template <typename C, typename... Args>
  std::optional<ComponentHandle<C>> addComponent(const Entity::ID &id,
                                                 Args &&...args) {
    if (not isValid(id)) {
      return std::nullopt;
    }

    auto componentFamilyOpt{getComponentFamily<C>()};
    if (not componentFamilyOpt) {
      return std::nullopt;
    }

    const BaseComponent::Family family{*componentFamilyOpt};
    UInt32 index{id.index()};
    if (m_entityComponentMasks[index].test(family)) {
      return std::nullopt;
    }

    auto componentMemoryPoolOpt{accomodateComponent<C>()};
    if (not componentMemoryPoolOpt) {
      return std::nullopt;
    }

    MemoryPool<C> *componentMemoryPool{*componentMemoryPoolOpt};
    componentMemoryPool->construct(index, std::forward<Args>(args)...);

    m_entityComponentMasks[index].set(family);

    ComponentHandle<C> componentHandle(this, id);
    m_eventDispatcher->enqueue<ComponentAddedEvent<C>>(Entity(this, id),
                                                       *componentHandle);

    return componentHandle;
  }

  template <typename C>
  bool removeComponent(const Entity::ID &id) {
    if (not isValid(id)) {
      return false;
    }

    auto componentFamilyOpt{getComponentFamily<C>()};
    if (not componentFamilyOpt) {
      return false;
    }

    const BaseComponent::Family family{*componentFamilyOpt};

    BaseMemoryPool *componentMemoryPool{m_componentMemoryPools[family]};
    ComponentHandle<C> componentHandle(this, id);
    m_eventDispatcher->enqueue<ComponentRemovedEvent<C>>(Entity(this, id),
                                                         *componentHandle);

    m_entityComponentMasks[id.index()].reset(family);

    componentMemoryPool->destroy(id.index());
    return true;
  }

  [[nodiscard]] bool hasComponent(const Entity::ID &id,
                                  BaseComponent::Family family) const {
    if (not isValid(id)) {
      return false;
    }

    if (family >= m_componentMemoryPools.size()) {
      return false;
    }

    BaseMemoryPool *componentMemoryPool{m_componentMemoryPools[family]};

    if (componentMemoryPool == nullptr or
        not m_entityComponentMasks[id.index()][family]) {
      return false;
    }

    return true;
  }

  template <typename C>
  [[nodiscard]] bool hasComponent(const Entity::ID &id) const {
    if (not isValid(id)) {
      return false;
    }

    auto componentFamilyOpt{getComponentFamily<C>()};
    if (not componentFamilyOpt) {
      return false;
    }

    const BaseComponent::Family family{*componentFamilyOpt};

    if (family >= m_componentMemoryPools.size()) {
      return false;
    }

    BaseMemoryPool *componentMemoryPool{m_componentMemoryPools[family]};

    if (componentMemoryPool == nullptr or
        !m_entityComponentMasks[id.index()][family]) {
      return false;
    }

    return true;
  }

  [[nodiscard]] bool hasAnyComponent(const Entity::ID &id) const;

  template <typename C>
  [[nodiscard]] std::optional<ComponentHandle<C>> getComponent(
      const Entity::ID &id) {
    if (not isValid(id)) {
      return std::nullopt;
    }

    if (not hasComponent<C>(id)) {
      return std::nullopt;
    }

    return ComponentHandle<C>(this, id);
  }

  template <typename C>
  [[nodiscard]] std::optional<ComponentHandle<C, const EntityManager>>
  getComponent(const Entity::ID &id) const {
    if (not isValid(id)) {
      return std::nullopt;
    }

    if (not hasComponent<C>(id)) {
      return std::nullopt;
    }

    return ComponentHandle<C, const EntityManager>(this, id);
  }

  template <typename... Components>
  [[nodiscard]] std::tuple<std::optional<ComponentHandle<Components>>...>
  getComponents(const Entity::ID &id) {
    return std::make_tuple(getComponent<Components>(id)...);
  }

  template <typename... Components>
  [[nodiscard]] std::tuple<
      std::optional<ComponentHandle<const Components, const EntityManager>>...>
  getComponents(const Entity::ID &id) const {
    return std::make_tuple(getComponent<const Components>(id)...);
  }

  template <typename... Components>
  [[nodiscard]] View entitiesWithComponents() {
    auto componentMask{createComponentMask<Components...>()};

    return View(this, componentMask);
  }

  template <typename... Components>
  [[nodiscard]] UnpackingView<Components...> entitiesWithComponents(
      ComponentHandle<Components> &...components) {
    auto componentMask{createComponentMask<Components...>()};

    return UnpackingView<Components...>(this, componentMask, components...);
  }

  [[nodiscard]] DebugView entities() { return DebugView(this); }

  template <typename C>
  bool unpack(const Entity::ID &id, ComponentHandle<C> &componentHandle) {
    if (not isValid(id)) {
      return false;
    }

    auto componentHandleOpt{getComponent<C>(id)};
    if (not componentHandleOpt) {
      return false;
    }

    componentHandle = *componentHandleOpt;
    return true;
  }

  template <typename C1, typename... Cn>
  bool unpack(const Entity::ID &id, ComponentHandle<C1> &componentHandle,
              ComponentHandle<Cn> &...others) {
    if (not isValid(id)) {
      return false;
    }

    auto componentHandleOpt{getComponent<C1>(id)};
    if (not componentHandleOpt) {
      return false;
    }

    componentHandle = *componentHandleOpt;
    return unpack<Cn...>(id, others...);
  }

  template <typename C>
  [[nodiscard]] static std::optional<BaseComponent::Family>
  getComponentFamily() {
    return Component<typename std::remove_const_t<C>>::getFamily();
  }

 private:
  friend class Entity;

  template <typename C, typename EM>
  friend class ComponentHandle;

  [[nodiscard]] bool isEntityIndexValid(const Entity::ID &id) const {
    return id.index() < m_entityIdsVersion.size();
  }

  [[nodiscard]] bool isEntityVersionValid(const Entity::ID &id) const {
    return m_entityIdsVersion[id.index()] == id.version();
  }

  template <typename C>
  [[nodiscard]] std::optional<C *> getComponentPtr(const Entity::ID &id) {
    if (not isValid(id)) {
      return std::nullopt;
    }

    auto componentFamilyOpt{getComponentFamily<C>()};
    if (not componentFamilyOpt) {
      return std::nullopt;
    }

    const BaseComponent::Family family{*componentFamilyOpt};

    BaseMemoryPool *componentMemoryPool{m_componentMemoryPools[family]};

    if (componentMemoryPool == nullptr) {
      return std::nullopt;
    }

    return static_cast<C *>(componentMemoryPool->get(id.index()));
  }

  template <typename C>
  [[nodiscard]] std::optional<const C *> getComponentPtr(
      const Entity::ID &id) const {
    if (not isValid(id)) {
      return std::nullopt;
    }

    auto componentFamilyOpt{getComponentFamily<C>()};
    if (not componentFamilyOpt) {
      return std::nullopt;
    }

    const BaseComponent::Family family{*componentFamilyOpt};
    BaseMemoryPool *componentMemoryPool{m_componentMemoryPools[family]};

    if (componentMemoryPool == nullptr) {
      return std::nullopt;
    }

    return static_cast<const C *>(componentMemoryPool->get(id.index()));
  }

  [[nodiscard]] std::optional<ComponentMask> getComponentMask(
      const Entity::ID &id) {
    if (not isValid(id)) {
      return std::nullopt;
    }

    if (id.index() >= m_entityComponentMasks.size()) {
      return std::nullopt;
    }

    return m_entityComponentMasks.at(id.index());
  }

  template <typename C>
  [[nodiscard]] ComponentMask createComponentMask() {
    ComponentMask mask;
    auto componentFamilyOpt{getComponentFamily<C>()};
    if (not componentFamilyOpt) {
      return mask;
    }

    const BaseComponent::Family family{*componentFamilyOpt};
    mask.set(family);

    return mask;
  }

  template <typename C1, typename C2, typename... Cn>
  [[nodiscard]] ComponentMask createComponentMask() {
    return createComponentMask<C1>() | createComponentMask<C2, Cn...>();
  }

  template <typename C>
  [[nodiscard]] ComponentMask createComponentMask(
      [[maybe_unused]] const ComponentHandle<C> &componentHandle) {
    return createComponentMask<C>();
  }

  template <typename C1, typename... Cn>
  [[nodiscard]] ComponentMask createComponentMask(
      [[maybe_unused]] const ComponentHandle<C1> &componentHandle1,
      [[maybe_unused]] const ComponentHandle<Cn> &...others) {
    return createComponentMask<C1, Cn...>();
  }

  void accomodateEntity(UInt32 index) {
    if (m_entityComponentMasks.size() <= index) {
      m_entityComponentMasks.resize(static_cast<std::size_t>(index) + 1);
      m_entityIdsVersion.resize(static_cast<std::size_t>(index) + 1);

      for (BaseMemoryPool *componentMemoryPool : m_componentMemoryPools) {
        if (componentMemoryPool) {
          componentMemoryPool->resize(static_cast<std::size_t>(index) + 1);
        }
      }
    }
  }

  template <typename C>
  [[nodiscard]] std::optional<MemoryPool<C> *> accomodateComponent() {
    auto componentFamilyOpt{getComponentFamily<C>()};
    if (not componentFamilyOpt) {
      return std::nullopt;
    }

    const BaseComponent::Family family{*componentFamilyOpt};
    if (m_componentMemoryPools.size() <= family) {
      m_componentMemoryPools.resize(static_cast<std::size_t>(family) + 1,
                                    nullptr);
    }

    if (m_componentMemoryPools[family] == nullptr) {
      MemoryPool<C> *componentMemoryPool{new MemoryPool<C>()};
      componentMemoryPool->resize(m_indexCounter);
      m_componentMemoryPools[family] = componentMemoryPool;
    }

    return static_cast<MemoryPool<C> *>(m_componentMemoryPools[family]);
  }

 private:
  UInt32 m_indexCounter{0};

  Ref<EventDispatcher> m_eventDispatcher;
  std::vector<BaseMemoryPool *> m_componentMemoryPools;
  std::vector<ComponentMask> m_entityComponentMasks;
  std::vector<UInt32> m_entityIdsVersion;
  std::vector<UInt32> m_freeEntityIds;
};
// ---------------------------------------------------------------------- //
// ---------------------------------------------------------------------- //

// ---------------------------------------------------------------------- //
// Methods definitions -------------------------------------------------- //
// ---------------------------------------------------------------------- //

// Entity methods ------------------------------------------------------- //
[[nodiscard]] inline bool Entity::isValid() const {
  return m_entityManager != nullptr and m_entityManager->isValid(m_id);
}

inline void Entity::invalidate() {
  m_id = InvalidID;
  m_entityManager = nullptr;
}

template <typename C, typename... Args>
inline std::optional<ComponentHandle<C>> Entity::addComponent(Args &&...args) {
  if (not isValid()) {
    return std::nullopt;
  }

  return m_entityManager->addComponent<C>(m_id, std::forward<Args>(args)...);
}

template <typename C, typename... Args>
inline std::optional<ComponentHandle<C>> Entity::addComponentFromCopy(
    const C &component) {
  if (not isValid()) {
    return std::nullopt;
  }

  return m_entityManager->addComponent<C>(m_id,
                                          std::forward<const C &>(component));
}

template <typename C, typename... Args>
inline std::optional<ComponentHandle<C>> Entity::replaceComponent(
    Args &&...args) {
  if (not isValid()) {
    return std::nullopt;
  }

  auto componentHandleOpt{getComponent<C>()};
  if (componentHandleOpt) {
    auto componentPtr{componentHandleOpt.value().get()};
    if (componentPtr == nullptr) {
      return std::nullopt;
    }

    *(componentPtr) = C(std::forward<Args>(args)...);
  } else {
    return m_entityManager->addComponent<C>(m_id, std::forward<Args>(args)...);
  }

  return componentHandleOpt;
}

template <typename C>
inline bool Entity::removeComponent() {
  if (not isValid()) {
    return false;
  }

  if (not hasComponent<C>()) {
    return false;
  }

  return m_entityManager->removeComponent<C>(m_id);
}

template <typename C>
[[nodiscard]] inline std::optional<ComponentHandle<C>> Entity::getComponent() {
  if (not isValid()) {
    return std::nullopt;
  }

  return m_entityManager->getComponent<C>(m_id);
}

template <typename C>
[[nodiscard]] inline std::optional<
    const ComponentHandle<C, const EntityManager>>
Entity::getComponent() const {
  if (not isValid()) {
    return std::nullopt;
  }

  return const_cast<const EntityManager *>(m_entityManager)
      ->getComponent<C>(m_id);
}

template <typename... Components>
[[nodiscard]] inline std::tuple<std::optional<ComponentHandle<Components>>...>
Entity::getComponents() {
  return m_entityManager->getComponents<Components...>(m_id);
}

template <typename... Components>
[[nodiscard]] inline std::tuple<
    std::optional<ComponentHandle<const Components, const EntityManager>>...>
Entity::getComponents() const {
  return const_cast<const EntityManager *>(m_entityManager)
      ->getComponents<const Components...>(m_id);
}

[[nodiscard]] inline bool Entity::hasComponent(
    BaseComponent::Family family) const {
  if (not isValid()) {
    return false;
  }

  return m_entityManager->hasComponent(m_id, family);
}

template <typename C>
[[nodiscard]] inline bool Entity::hasComponent() const {
  if (not isValid()) {
    return false;
  }

  return m_entityManager->hasComponent<C>(m_id);
}

template <typename C1, typename... OtherComponents>
inline bool Entity::unpack(ComponentHandle<C1> &c1,
                           ComponentHandle<OtherComponents> &...others) {
  if (not isValid()) {
    return false;
  }

  return m_entityManager->unpack(m_id, c1, others...);
}

inline bool Entity::destroy() {
  if (not isValid()) {
    return false;
  }

  bool result{m_entityManager->destroyEntity(m_id)};
  invalidate();
  return result;
}

[[nodiscard]] inline std::optional<ComponentMask> Entity::getComponentMask()
    const {
  return m_entityManager->getComponentMask(m_id);
}
// ---------------------------------------------------------------------- //

template <typename C, typename EM>
[[nodiscard]] inline ComponentHandle<C, EM>::operator bool() const {
  return isValid();
}

// ComponentHandle methods ---------------------------------------------- //
template <typename C, typename EM>
[[nodiscard]] inline bool ComponentHandle<C, EM>::isValid() const {
  return m_entityManager != nullptr and m_entityManager->isValid(m_id) and
         m_entityManager->template hasComponent<C>(m_id);
}

template <typename C, typename EM>
[[nodiscard]] inline C *ComponentHandle<C, EM>::operator->() {
  NT_CORE_ASSERT(isValid());

  auto componentPtr{m_entityManager->template getComponentPtr<C>(m_id)};
  if (not componentPtr) {
    return nullptr;
  }

  return *componentPtr;
}

template <typename C, typename EM>
[[nodiscard]] inline const C *ComponentHandle<C, EM>::operator->() const {
  NT_CORE_ASSERT(isValid());

  auto componentPtr{m_entityManager->template getComponentPtr<C>(m_id)};
  if (not componentPtr) {
    return nullptr;
  }

  return *componentPtr;
}

template <typename C, typename EM>
[[nodiscard]] inline C *ComponentHandle<C, EM>::get() {
  NT_CORE_ASSERT(isValid());

  auto componentPtr{m_entityManager->template getComponentPtr<C>(m_id)};
  if (not componentPtr) {
    return nullptr;
  }

  return *componentPtr;
}

template <typename C, typename EM>
[[nodiscard]] inline const C *ComponentHandle<C, EM>::get() const {
  NT_CORE_ASSERT(isValid());

  auto componentPtr{m_entityManager->template getComponentPtr<C>(m_id)};
  if (not componentPtr) {
    return nullptr;
  }

  return *componentPtr;
}

template <typename C, typename EM>
inline bool ComponentHandle<C, EM>::remove() {
  if (not isValid()) {
    return false;
  }

  return m_entityManager->template removeComponent<C>(m_id);
}
// ---------------------------------------------------------------------- //

}  // namespace Neat