
#pragma once

#include <any>

#include "Core/Types.hpp"

namespace Neat {
struct QueuedEvent {
  TypeID eventId;
  std::any event;
};
}  // namespace Neat