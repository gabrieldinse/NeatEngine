#include <iomanip>

#include "Neat/Math/VectorOperations.h"


namespace Neat
{
   // Relational operators
   template <typename T, SizeType N>
   inline constexpr
   Bool operator>(const Vec<N, T>& va, const Vec<N, T>& vb)
   {
      return (norm(va) > norm(vb));
   }

   template <typename T, SizeType N>
   inline constexpr
   Bool operator<(const Vec<N, T>& va, const Vec<N, T>& vb)
   {
      return (vb > va);
   }

   template <typename T, SizeType N>
   inline constexpr
   Bool operator==(const Vec<N, T>& va, const Vec<N, T>& vb)
   {
      return (norm(va) == norm(vb));
   }

   template <typename T, SizeType N>
   inline constexpr
   Bool operator!=(const Vec<N, T>& va, const Vec<N, T>& vb)
   {
      return !(va == vb);
   }

   template <typename T, SizeType N>
   inline constexpr
   Bool operator>=(const Vec<N, T>& va, const Vec<N, T>& vb)
   {
      return !(va < vb);
   }

   template <typename T, SizeType N>
   inline constexpr
   Bool operator<=(const Vec<N, T>& va, const Vec<N, T>& vb)
   {
      return !(va > vb);
   }


   template <typename T, SizeType N>
   std::ostream& operator<<(std::ostream& os, const Vec<N, T>& v)
   {
      os << "[";
      for (SizeType i = 0; i < N; ++i)
      {
         if (i < N - 1)
            os << std::setw(10) << std::setprecision(6)
               << v[i] << ", ";
         else
            os << std::setw(10) << std::setprecision(6)
               << v[i];
      }
      os << "]\n";

      return os;
   }
}