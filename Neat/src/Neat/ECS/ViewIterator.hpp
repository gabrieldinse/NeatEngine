#pragma once

#include <iterator>

namespace Neat {

  template <class DelegatedIterator, bool IterateOverAll = false>
  class ViewIterator {
   public:
    using iterator_category = std::input_iterator_tag;
    using value_type = EntityId;
    using difference_type = PtrDiffType;
    using pointer = value_type *;
    using reference = value_type &;

   public:
    DelegatedIterator &operator++() {
      ++m_pos;
      next();

      return *static_cast<DelegatedIterator *>(this);
    }

    Entity operator*() {
      return Entity(m_entityManager, m_entityManager->createId(m_pos));
    }

    const Entity operator*() const {
      return Entity(m_entityManager, m_entityManager->createId(m_pos));
    }

    bool operator==(const DelegatedIterator &rhs) const {
      return m_pos == rhs.m_pos;
    }

    bool operator!=(const DelegatedIterator &rhs) const {
      return m_pos != rhs.m_pos;
    }

   protected:
    ViewIterator(EntityManager *entityManager, UInt32 index)
        : m_entityManager(entityManager),
          m_pos(index),
          m_capacity(m_entityManager->capacity()),
          m_freeCursor(UInt32Max) {
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
          m_freeCursor(UInt32Max) {
      if (IterateOverAll) {
        std::sort(m_entityManager->m_freeEntityIds.begin(),
                  m_entityManager->m_freeEntityIds.end());
        m_freeCursor = 0;
      }
    }

    void next() {
      while (m_pos < m_capacity and not((IterateOverAll and IsValidEntity()) or
                                        matchComponentMask())) {
        ++m_pos;
      }

      if (m_pos < m_capacity) {
        Entity entity =
            m_entityManager->getEntity(m_entityManager->createId(m_pos));
        static_cast<DelegatedIterator *>(this)->nextEntity(entity);
      }
    }

    bool matchComponentMask() const {
      return (m_entityManager->m_entityComponentMasks[m_pos] &
              m_componentGroupMask) == m_componentGroupMask;
    }

    bool IsValidEntity() {
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
    SizeType m_capacity;
    SizeType m_freeCursor;
  };
}  // namespace Neat