#pragma once

#include <limits>

#include "Neat/Core/Types.hpp"


namespace Neat
{
   constexpr Int8              Int8Min = INT8_MIN;
   constexpr Int8              Int8Max = INT8_MAX;
   constexpr UInt8             UInt8Max = UINT8_MAX;
   constexpr Int8              ByteMin = Int8Min;
   constexpr Int8              ByteMax = Int8Max;
   constexpr UInt8             UByteMax = UInt8Max;
   constexpr Int16             Int16Min = INT16_MIN;
   constexpr Int16             Int16Max = INT16_MAX;
   constexpr UInt16            UInt16Max = UINT16_MAX;
   constexpr Int32             Int32Min = INT32_MIN;
   constexpr Int32             Int32Max = INT32_MAX;
   constexpr UInt32            UInt32Max = UINT32_MAX;
   constexpr Int64             Int64Min = INT64_MIN;
   constexpr Int64             Int64Max = INT64_MAX;
   constexpr UInt64            UInt64Max = INT64_MIN;

   constexpr IntMaxType        IntMaxTypeMin = INTMAX_MIN;
   constexpr IntMaxType        IntMaxTypeMax = INTMAX_MAX;
   constexpr UIntMaxType       UIntMaxTypeMax = UINTMAX_MAX;

   constexpr IntPointerType    IntPointerMin = INTPTR_MIN;
   constexpr IntPointerType    IntPointerMax = INTPTR_MAX;
   constexpr UIntPointerType   UIntPointerMax = UINTPTR_MAX;

   constexpr char              CharMin = CHAR_MIN;
   constexpr char              CharMax = CHAR_MAX;
   constexpr unsigned char     UCharMax = UCHAR_MAX;



   template <typename T>
   inline constexpr T epsilon = std::numeric_limits<T>::epsilon();

   template <typename T>
   inline constexpr T infinity = std::numeric_limits<T>::infinity();

   template <typename T>
   inline constexpr T nan = std::numeric_limits<T>::quiet_NaN();

   template <typename T>
   inline constexpr T signalNan = std::numeric_limits<T>::signaling_NaN();
}