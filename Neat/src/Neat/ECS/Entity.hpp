#pragma once

#include <bitset>
#include <ostream>
#include <tuple>
#include <type_traits>

#include "Neat/ECS/EntityId.hpp"

namespace Neat {
class EntityManager;

template <typename C, typename EM = EntityManager>
class ComponentHandle;

using ComponentMask = std::bitset<maxComponents>;
class Entity {
 public:
  Entity() = default;
  Entity(EntityManager *entityManager, EntityId id)
      : m_entityManager(entityManager), m_id(id) {}
  Entity(const Entity &entity) = default;

  Entity &operator=(const Entity &entity) = default;

  explicit operator bool() const { return isValid(); }

  bool operator!=(const Entity &other) const { return not(other == *this); }

  bool operator<(const Entity &other) const { return other.m_id < m_id; }

  EntityId id() const { return m_id; }

  bool isValid() const;
  void invalidate();

  template <typename C, typename... Args>
  ComponentHandle<C> addComponent(Args &&...args);

  template <typename C, typename... Args>
  ComponentHandle<C> addComponentFromCopy(const C &component);

  template <typename C, typename... Args>
  ComponentHandle<C> replaceComponent(Args &&...args);

  template <typename C>
  void removeComponent();

  template <typename C,
            typename = typename std::enable_if_t<!std::is_const<C>::value>>
  ComponentHandle<C> getComponent();

  template <typename C,
            typename = typename std::enable_if_t<std::is_const<C>::value>>
  const ComponentHandle<C, const EntityManager> getComponent() const;

  template <typename... Components>
  std::tuple<ComponentHandle<Components>...> getComponents();

  template <typename... Components>
  std::tuple<ComponentHandle<const Components, const EntityManager>...>
  getComponents() const;

  template <typename C>
  bool hasComponent() const;

  template <typename C1, typename... OtherComponents>
  void unpack(ComponentHandle<C1> &c1,
              ComponentHandle<OtherComponents> &...others);

  void destroy();

  ComponentMask getComponentMask() const;

 private:
  void checkIsValid() const;

 private:
  EntityManager *m_entityManager = nullptr;
  EntityId m_id = INVALID_ID;
};

std::ostream &operator<<(std::ostream &os, const Entity &entity);

template <typename C, typename... Args>
inline ComponentHandle<C> Entity::addComponent(Args &&...args) {
  checkIsValid();

  return m_entityManager->addComponent<C>(m_id, std::forward<Args>(args)...);
}

template <typename C, typename... Args>
inline ComponentHandle<C> Entity::addComponentFromCopy(const C &component) {
  checkIsValid();

  return m_entityManager->addComponent<C>(m_id,
                                          std::forward<const C &>(component));
}

template <typename C, typename... Args>
inline ComponentHandle<C> Entity::replaceComponent(Args &&...args) {
  checkIsValid();

  auto component_handle = getComponent<C>();
  if (component_handle)
    *(component_handle.get()) = C(std::forward<Args>(args)...);
  else
    component_handle =
        m_entityManager->addComponent<C>(m_id, std::forward<Args>(args)...);

  return component_handle;
}

template <typename C>
inline void Entity::removeComponent() {
  checkIsValid();

  if (not hasComponent<C>()) throw ComponentNotPresentError();

  m_entityManager->removeComponent<C>(m_id);
}

template <typename C, typename>
inline ComponentHandle<C> Entity::getComponent() {
  checkIsValid();

  return m_entityManager->getComponent<C>(m_id);
}

template <typename C, typename>
inline const ComponentHandle<C, const EntityManager> Entity::getComponent()
    const {
  checkIsValid();

  return const_cast<const EntityManager *>(m_entityManager)
      ->getComponent<const C>(m_id);
}

template <typename... Components>
inline std::tuple<ComponentHandle<Components>...> Entity::getComponents() {
  checkIsValid();

  return m_entityManager->getComponents<Components...>(m_id);
}

template <typename... Components>
inline std::tuple<ComponentHandle<const Components, const EntityManager>...>
Entity::getComponents() const {
  checkIsValid();

  return const_cast<const EntityManager *>(m_entityManager)
      ->getComponents<const Components...>(m_id);
}

template <typename C>
inline bool Entity::hasComponent() const {
  checkIsValid();

  return m_entityManager->hasComponent<C>(m_id);
}

template <typename C1, typename... OtherComponents>
inline void Entity::unpack(ComponentHandle<C1> &c1,
                           ComponentHandle<OtherComponents> &...others) {
  checkIsValid();

  m_entityManager->unpack(m_id, c1, others...);
}

inline void Entity::destroy() {
  checkIsValid();

  m_entityManager->destroyEntity(m_id);
  invalidate();
}

inline std::bitset<maxComponents> Entity::getComponentMask() const {
  return m_entityManager->getComponentMask(m_id);
}
}  // namespace Neat