#pragma once

#include "Neat/ECS/Component.hpp"

namespace Neat {
class EntityManager;
  template <bool IterateOverAll>
  class BaseView {
   public:
    Iterator begin() {
      return Iterator(m_entityManager, m_componentGroupMask, 0);
    }

    Iterator end() {
      return Iterator(m_entityManager, m_componentGroupMask,
                      (UInt32)m_entityManager->capacity());
    }

    const Iterator begin() const {
      return Iterator(m_entityManager, m_componentGroupMask, 0);
    }

    const Iterator end() const {
      return Iterator(m_entityManager, m_componentGroupMask,
                      (UInt32)m_entityManager->capacity());
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
}  // namespace Neat