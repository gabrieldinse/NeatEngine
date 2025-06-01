#pragma once

#include "Neat/ECS/ComponentHandle.hpp"
#include "Neat/ECS/Entity.hpp"

namespace Neat {

class EntityManager;
    template <typename... Components>
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
}  // namespace Neat