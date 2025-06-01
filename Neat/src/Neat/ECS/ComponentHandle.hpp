#pragma once

#include <bitset>
#include <iterator>
#include <ostream>
#include <type_traits>


namespace Neat {
class EntityManager;

template <typename C, typename EM>
class ComponentHandle {
 public:
  ComponentHandle() : m_entityManager(nullptr) {}

  explicit operator bool() const;
  bool isValid() const;

  C *operator->();
  const C *operator->() const;
  C *get();
  const C *get() const;

  void remove();

  bool operator==(const ComponentHandle<C> &other) const {
    return m_entityManager == other.m_entityManager and m_id == other.m_id;
  }

  bool operator!=(const ComponentHandle<C> &other) const {
    return not(*this == other);
  }

 private:
  friend class EntityManager;

  ComponentHandle(EM *entityManager, const Entity::Id &id)
      : m_entityManager(entityManager), m_id(id) {}

  void checkIsValid() const;

 private:
  EM *m_entityManager;
  Entity::Id m_id;
};

template <typename C, typename EM>
inline ComponentHandle<C, EM>::operator bool() const {
  return isValid();
}

template <typename C, typename EM>
inline bool ComponentHandle<C, EM>::isValid() const {
  return m_entityManager != nullptr and !m_entityManager->isValid(m_id) and
         m_entityManager->template hasComponent<C>(m_id);
}

template <typename C, typename EM>
inline void ComponentHandle<C, EM>::checkIsValid() const {
  if (m_entityManager == nullptr)
    throw InvalidComponentError("Assigned EntityManager is null.");

  try {
    m_entityManager->checkIsValid(m_id);
  } catch (const EntityError &e) {
    throw InvalidComponentError("Assigned Entity is invalid.\n" + e.msg());
  }

  if (not m_entityManager->template hasComponent<C>(m_id))
    throw InvalidComponentError();
}

template <typename C, typename EM>
inline C *ComponentHandle<C, EM>::operator->() {
  checkIsValid();

  return m_entityManager->template getComponentPtr<C>(m_id);
}

template <typename C, typename EM>
inline const C *ComponentHandle<C, EM>::operator->() const {
  checkIsValid();

  return m_entityManager->template getComponentPtr<C>(m_id);
}

template <typename C, typename EM>
inline C *ComponentHandle<C, EM>::get() {
  checkIsValid();

  return m_entityManager->template getComponentPtr<C>(m_id);
}

template <typename C, typename EM>
inline const C *ComponentHandle<C, EM>::get() const {
  checkIsValid();

  return m_entityManager->template getComponentPtr<C>(m_id);
}

template <typename C, typename EM>
inline void ComponentHandle<C, EM>::remove() {
  checkIsValid();

  m_entityManager->template remove<C>(m_id);
}
}  // namespace Neat