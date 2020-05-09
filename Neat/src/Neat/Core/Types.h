#pragma once

#include <cstdint>
#include <cstddef>
#include <climits>


namespace Neat
{
   // Custom types
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
   using SizeType    = std::size_t;
   using Bool        = bool;
   using Float       = float;
   using Double      = double;
   using Char        = char;
   using UChar       = unsigned char;


   // Limits
   constexpr Int8        int8_min         = INT8_MIN;
   constexpr Int8        int8_max         = INT8_MAX;
   constexpr UInt8       uint8_max        = UINT8_MAX;
   constexpr Int8        byte_min         = int8_min;
   constexpr Int8        byte_max         = int8_max;
   constexpr UInt8       ubyte_max        = uint8_max;
   constexpr IntShort    int_short_min    = INT16_MIN;
   constexpr IntShort    int_short_max    = INT16_MAX;
   constexpr UIntShort   uint_short_max   = UINT16_MAX;
   constexpr Int         int_min          = INT32_MIN;
   constexpr Int         int_max          = INT32_MAX;
   constexpr UInt        uint_max         = UINT32_MAX;
   constexpr IntLong     int_long_min     = INT64_MIN;
   constexpr IntLong     int_long_max     = INT64_MAX;
   constexpr UIntLong    uint_long_max    = UINT64_MAX;
   constexpr Char        char_min         = CHAR_MIN;
   constexpr Char        char_max         = CHAR_MAX;
   constexpr UChar       uchar_max        = UCHAR_MAX;
}