#pragma once

#include "Neat/ECS/Entity.hpp"
#include "Neat/ECS/ViewIterator.hpp"

namespace Neat {
class EntityManager;

    class Iterator : public ViewIterator<Iterator> {
     public:
      Iterator(EntityManager *entityManager,
               const ComponentMask componentGroupMask, UInt32 index)
          : ViewIterator<Iterator>(entityManager,
                                                   componentGroupMask, index) {
        ViewIterator<Iterator>::next();
      }

      void nextEntity(Entity &entity) {}
    };
}  // namespace Neat