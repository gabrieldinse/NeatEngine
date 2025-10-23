
#pragma once

#include <any>

#include "Utils/TypeID.hpp"
#include "Core/Types.hpp"

namespace Neat {
struct QueuedEvent {
  TypeID eventId;
  std::any event;
};
}  // namespace Neat