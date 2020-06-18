#include <iomanip>


namespace Neat
{
   template <typename T, UInt32 N>
   std::ostream& operator<<(std::ostream& os, const Vector<N, T>& v)
   {
      os << "Neat::Vector<" << N << ", " << typeid(T).name() << "> [";
      for (UInt32 i = 0; i < N; ++i)
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