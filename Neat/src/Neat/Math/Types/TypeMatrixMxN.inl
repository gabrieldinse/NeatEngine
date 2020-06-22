#include <iomanip>


namespace Neat
{
   template <UInt32 M, UInt32 N, typename T>
   std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& m)
   {
      os << "Neat::Matrix<" << N << ", " << M << ", " << typeid(T).name()
         << ">\n[";
      for (std::size_t i = 0; i < M; ++i)
      {
         if (i == 0)
            os << "[";
         else
            os << "\n [";
         for (std::size_t j = 0; j < N; ++j)
         {
            if (j < N - 1)
               os << std::setw(10) << std::setprecision(6)
                  << m[i][j] << ", ";
            else
               os << std::setw(10) << std::setprecision(6)
                  << m[i][j];
         }
         os << "]";
      }
      os << "]";

      return os;
   }
}