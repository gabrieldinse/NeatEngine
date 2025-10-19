#pragma once

#include <cstddef>

#include "Types.hpp"
#include "Limits.hpp"

namespace Neat {
constexpr SizeType MaxComponents = 64;

constexpr TypeID NoneType = 0;
constexpr InstanceID NoneInstance = 0;

constexpr LayerID NoneLayer = Limits::Max<LayerID>;
constexpr LayerID MaxLayers = NoneLayer - 1;

constexpr EventPriority EventPriorityHighest = 0;
constexpr EventPriority EventPriorityLowest = Limits::Max<UInt16>;

}  // namespace Neat
