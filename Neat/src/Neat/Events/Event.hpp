#pragma once

#include "Neat/Events/BaseEvent.hpp"

namespace Neat {
class EventManager;

template <typename Derived>
class Event : public BaseEvent {
 private:
  friend class EventManager;

  static Family getFamily() {
    static Family family = s_familyCounter++;
    return family;
  }
};
}  // namespace Neat