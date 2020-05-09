#pragma once

#include <stdexcept>


namespace Neat
{
   struct Exception : public std::runtime_error
   {
      Exception(const char* msg) : std::runtime_error(msg) {}
   };

   struct DimensionError : public Exception
   {
      DimensionError(const char* msg) : Exception(msg) {}
   };

   struct VecDimensionError : public DimensionError
   {
      VecDimensionError(const char* msg) : DimensionError(msg) {}
   };

   struct MatDimensionError : public DimensionError
   {
      MatDimensionError(const char* msg) : DimensionError(msg) {}
   };
}