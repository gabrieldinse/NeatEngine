#include <iomanip>

#include "Neat/Math/VectorOperations.h"


namespace Neat
{
   // Relational operators
   template <typename T, UInt32 N>
   inline constexpr
   bool operator>(const Vector<N, T>& va, const Vector<N, T>& vb)
   {
      return (norm(va) > norm(vb));
   }

   template <typename T, UInt32 N>
   inline constexpr
   bool operator<(const Vector<N, T>& va, const Vector<N, T>& vb)
   {
      return (vb > va);
   }

   template <typename T, UInt32 N>
   inline constexpr
   bool operator==(const Vector<N, T>& va, const Vector<N, T>& vb)
   {
      return (norm(va) == norm(vb));
   }

   template <typename T, UInt32 N>
   inline constexpr
   bool operator!=(const Vector<N, T>& va, const Vector<N, T>& vb)
   {
      return !(va == vb);
   }

   template <typename T, UInt32 N>
   inline constexpr
   bool operator>=(const Vector<N, T>& va, const Vector<N, T>& vb)
   {
      return !(va < vb);
   }

   template <typename T, UInt32 N>
   inline constexpr
   bool operator<=(const Vector<N, T>& va, const Vector<N, T>& vb)
   {
      return !(va > vb);
   }


   template <typename T, UInt32 N>
   std::ostream& operator<<(std::ostream& os, const Vector<N, T>& v)
   {
      os << "Neat::Vector<" << N << ", " << typeid(T).name() << "> [";
      for (std::size_t i = 0; i < N; ++i)
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