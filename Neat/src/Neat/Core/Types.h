#pragma once

#include <cstdint>
#include <cstddef>
#include <climits>


namespace Neat
{
   // Main types
   using Int8        = int8_t;
   using UInt8       = uint8_t;
   using Byte        = Int8;
   using UByte       = UInt8;
   using IntShort    = int16_t;
   using UIntShort   = uint16_t;
   using Int         = int32_t;
   using UInt        = uint32_t;
   using IntLong     = int64_t;
   using UIntLong    = uint64_t;


   // Limits
   constexpr Int8            NT_INT8_MIN         = INT8_MIN;
   constexpr Int8            NT_INT8_MAX         = INT8_MAX;
   constexpr UInt8           NT_UINT8_MAX        = UINT8_MAX;
   constexpr Int8            NT_BYTE_MIN         = NT_INT8_MIN;
   constexpr Int8            NT_BYTE_MAX         = NT_INT8_MAX;
   constexpr UInt8           NT_UBYTE_MAX        = NT_UINT8_MAX;
   constexpr IntShort        NT_INT_SHORT_MIN    = INT16_MIN;
   constexpr IntShort        NT_INT_SHORT_MAX    = INT16_MAX;
   constexpr UIntShort       NT_UINT_SHORT_MAX   = UINT16_MAX;
   constexpr Int             NT_INT_MIN          = INT32_MIN;
   constexpr Int             NT_INT_MAX          = INT32_MAX;
   constexpr UInt            NT_UINT_MAX         = UINT32_MAX;
   constexpr IntLong         NT_INT_LONG_MIN     = INT64_MIN;
   constexpr IntLong         NT_INT_LONG_MAX     = INT64_MAX;
   constexpr UIntLong        NT_UINT_LONG_MAX    = UINT64_MAX;
   constexpr char            NT_CHAR_MIN         = CHAR_MIN;
   constexpr char            NT_CHAR_MAX         = CHAR_MAX;
   constexpr unsigned char   NT_UCHAR_MAX        = UCHAR_MAX;


   // Custom types
   using Timestep = double;
}