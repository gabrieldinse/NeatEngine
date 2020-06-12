#pragma once

#include <cstdint>
#include <cstddef>
#include <climits>


namespace Neat
{
   // Main types
   using Int8              = int8_t;
   using UInt8             = uint8_t;
   using Byte              = Int8;
   using UByte             = UInt8;
   using Int16             = int16_t;
   using UInt16            = uint16_t;
   using Int32             = int32_t;
   using UInt32            = uint32_t;
   using Int64             = int64_t;
   using UInt64            = uint64_t;

   using IntMaxType        = intmax_t;
   using UIntMaxType       = uintmax_t;

   using IntPointerType    = intptr_t;
   using UIntPointerType   = uintptr_t;


   // Limits
   constexpr Int8              NT_INT8_MIN            = INT8_MIN;
   constexpr Int8              NT_INT8_MAX            = INT8_MAX;
   constexpr UInt8             NT_UINT8_MAX           = UINT8_MAX;
   constexpr Int8              NT_BYTE_MIN            = NT_INT8_MIN;
   constexpr Int8              NT_BYTE_MAX            = NT_INT8_MAX;
   constexpr UInt8             NT_UBYTE_MAX           = NT_UINT8_MAX;
   constexpr Int16             NT_INT16_MIN           = INT16_MIN;
   constexpr Int16             NT_INT16_MAX           = INT16_MAX;
   constexpr UInt16            NT_UINT16_MAX          = UINT16_MAX;
   constexpr Int32             NT_INT32_MIN           = INT32_MIN;
   constexpr Int32             NT_INT32_MAX           = INT32_MAX;
   constexpr UInt32            NT_UINT32_MAX          = UINT32_MAX;
   constexpr Int64             NT_INT64_MIN           = INT64_MIN;
   constexpr Int64             NT_INT64_MAX           = INT64_MAX;
   constexpr UInt64            NT_UINT64_MAX          = INT64_MIN;

   constexpr IntMaxType        NT_INT_MAX_TYPE_MIN    = INTMAX_MIN;
   constexpr IntMaxType        NT_INT_MAX_TYPE_MAX    = INTMAX_MAX;
   constexpr UIntMaxType       NT_UINT_MAX_TYPE_MAX   = UINTMAX_MAX;

   constexpr IntPointerType    NT_INT_PTR_MIN         = INTPTR_MIN;
   constexpr IntPointerType    NT_INT_PTR_MAX         = INTPTR_MAX;
   constexpr UIntPointerType   NT_UINT_PTR_MAX        = UINTPTR_MAX;

   constexpr char              NT_CHAR_MIN            = CHAR_MIN;
   constexpr char              NT_CHAR_MAX            = CHAR_MAX;
   constexpr unsigned char     NT_UCHAR_MAX           = UCHAR_MAX;


   // Custom types
   using DeltaTime = double;
}