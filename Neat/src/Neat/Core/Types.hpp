#pragma once

#include <climits>
#include <cstddef>
#include <cstdint>

namespace Neat {
// Main types
using Int8 = int8_t;
using UInt8 = uint8_t;
using Byte = Int8;
using UByte = UInt8;
using Int16 = int16_t;
using UInt16 = uint16_t;
using Int32 = int32_t;
using UInt32 = uint32_t;
using Int64 = int64_t;
using UInt64 = uint64_t;

using Int = int;
using Uint = unsigned;

using SizeType = size_t;

using IntMaxType = intmax_t;
using UIntMaxType = uintmax_t;

using IntPointerType = intptr_t;
using UIntPointerType = uintptr_t;

// Custom types
using DeltaTime = double;
}  // namespace Neat