#pragma once

#include <algorithm>
#include <bitset>
#include <iterator>
#include <ostream>
#include <queue>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

#include "Neat/Core/Limits.hpp"
#include "Neat/Core/Log.hpp"
#include "Neat/Core/Types.hpp"
#include "Neat/ECS/BaseView.hpp"
#include "Neat/Events/Event.hpp"
#include "Neat/Events/EventManager.hpp"
#include "Neat/Helper/MemoryPool.hpp"
#include "Neat/Helper/NonCopyable.hpp"

namespace Neat {
class EntityManager;

template <typename C, typename EM = EntityManager>
class ComponentHandle;
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
        std::get<N>(m_componentHandles) = entity.getComponent<C>();
      }

      template <std::size_t N, typename C1, typename C2, typename... Cn>
      void unpackNComponents(Entity &entity) const {
        std::get<N>(m_componentHandles) = entity.getComponent<C1>();
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
    Iterator begin() {
      return Iterator(m_entityManager, m_componentGroupMask, 0, m_unpacker);
    }

    Iterator end() {
      return Iterator(m_entityManager, m_componentGroupMask,
                      (UInt32)m_entityManager->capacity(), m_unpacker);
    }

    const Iterator begin() const {
      return Iterator(m_entityManager, m_componentGroupMask, 0, m_unpacker);
    }

    const Iterator end() const {
      return Iterator(m_entityManager, m_componentGroupMask,
                      (UInt32)m_entityManager->capacity(), m_unpacker);
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
}  // namespace Neat