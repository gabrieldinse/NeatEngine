#pragma once

#include <memory>
#include <type_traits>

#include <climits>
#include <cstddef>
#include <cstdint>

namespace Neat {
using Int8 = std::int8_t;
using UInt8 = std::uint8_t;
using Byte = Int8;
using UByte = UInt8;
using Int16 = std::int16_t;
using UInt16 = std::uint16_t;
using Int32 = std::int32_t;
using UInt32 = std::uint32_t;
using Int64 = std::int64_t;
using UInt64 = std::uint64_t;

using Int = int;
using UInt = unsigned;
using Short = short;
using UShort = unsigned short;
using Long = long;
using ULong = unsigned long;
using LLong = long long;
using ULLong = unsigned long long;

using SizeType = std::size_t;

using IntMaxType = std::intmax_t;
using UIntMaxType = std::uintmax_t;

using IntPointerType = std::intptr_t;
using UIntPointerType = std::uintptr_t;

using Float = float;
using Double = double;
using LDouble = long double;
using Bool = bool;
using Char = char;
using UChar = unsigned char;

using TypeID = UIntPointerType;
using InstanceID = UIntPointerType;
using LayerID = UInt32;
using EventPriority = UInt16;

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using WeakRef = std::weak_ptr<T>;

template <typename T, typename... Args>
Scope<T> makeScope(Args &&...args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
Ref<T> makeRef(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T, typename U>
  requires std::is_base_of_v<U, T>
Ref<T> staticCast(const Ref<U> &pointer) noexcept {
  return std::static_pointer_cast<T>(pointer);
}
}  // namespace Neat