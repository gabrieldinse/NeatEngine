#pragma once

#include "Neat/Core/Types.hpp"

namespace Neat {
enum class EventPriority : UInt16 { Lowest, Low, High, Normal, Highest };

bool operator<(EventPriority priorityA, EventPriority priorityB);
bool operator==(EventPriority priorityA, EventPriority priorityB);
}  // namespace Neat