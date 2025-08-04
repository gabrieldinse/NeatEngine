#pragma once

#include <memory>

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
using UInt = unsigned;
using Short = short;
using UShort = unsigned short;
using Long = long;
using ULong = unsigned long;
using LLong = long long;
using ULLong = unsigned long long;

using SizeType = size_t;

using IntMaxType = intmax_t;
using UIntMaxType = uintmax_t;

using IntPointerType = intptr_t;
using UIntPointerType = uintptr_t;

using Float = float;
using Double = double;
using LDouble = long double;
using Bool = bool;
using Char = char;
using UChar = unsigned char;

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using WeakRef = std::weak_ptr<T>;

template <typename T, typename... Args>
Scope<T> makeScope(Args&&... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
Ref<T> makeRef(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
Scope<T> createScope(Args&&... args) {
  return makeScope<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
Ref<T> createRef(Args&&... args) {
  return makeRef<T>(std::forward<Args>(args)...);
}
}  // namespace Neat