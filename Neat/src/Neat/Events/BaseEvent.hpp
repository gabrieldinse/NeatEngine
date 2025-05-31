#pragma once

#include "Neat/Core/Types.hpp"

namespace Neat {
class EventManager;

class BaseEvent {
 public:
  using Family = UInt32;

  virtual ~BaseEvent() {}

 protected:
  static Family s_familyCounter;
};
}  // namespace Neat