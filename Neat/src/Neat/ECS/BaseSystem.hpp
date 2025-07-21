#pragma once

#include "Neat/Core/Types.hpp"
#include "Neat/Events/EventDispatcher.hpp"
#include "Neat/Utils/NonCopyable.hpp"

namespace Neat {
class EntityManager;

class BaseSystem : public NonCopyable {
 public:
  using Family = UInt32;

  virtual ~BaseSystem() = default;

  virtual void init(
      [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher) = 0;
  virtual void onUpdate(
      [[maybe_unused]] const Ref<EntityManager> &entityManager,
      [[maybe_unused]] const Ref<EventDispatcher> &eventDispatcher,
      double deltaTimeSeconds) = 0;

 protected:
  static Family s_familyCounter;
};
}  // namespace Neat