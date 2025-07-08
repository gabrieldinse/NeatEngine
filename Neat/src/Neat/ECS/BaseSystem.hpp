#pragma once

#include "Neat/Core/Types.hpp"
#include "Neat/Events/EventDispatcher.hpp"
#include "Neat/Misc/NonCopyable.hpp"

namespace Neat {
class EntityManager;

class BaseSystem : public NonCopyable {
 public:
  using Family = UInt32;

  virtual ~BaseSystem() = default;

  virtual void init([[maybe_unused]] const std::shared_ptr<EventDispatcher>
                        &eventDispatcher) = 0;
  virtual void onUpdate(
      [[maybe_unused]] const std::shared_ptr<EntityManager> &entityManager,
      [[maybe_unused]] const std::shared_ptr<EventDispatcher> &eventDispatcher,
      double deltaTimeSeconds) = 0;

 protected:
  static Family s_familyCounter;
};
}  // namespace Neat