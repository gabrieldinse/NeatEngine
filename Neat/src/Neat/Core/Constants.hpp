#pragma once

#include <cstddef>

#include "Types.hpp"
#include "Limits.hpp"

namespace Neat {
constexpr std::size_t MaxComponents = 64;

constexpr LayerID NoLayer = Limits::Max<LayerID>;
constexpr LayerID MaxLayers = NoLayer - 1;

constexpr EventPriority EventPriorityHighest = 0;
constexpr EventPriority EventPriorityLowest = Limits::Max<UInt16>;
}  // namespace Neat
