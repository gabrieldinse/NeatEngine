#include <iomanip>


namespace Neat
{
   template <std::size_t M, std::size_t N, typename T>
   std::ostream& operator<<(std::ostream& os, const Mat<M, N, T>& m)
   {
      os << "[[";
      for (std::size_t i = 0; i < M; ++i)
      {
         if (i > 0)
            std::cout << "\n [";

         for (std::size_t j = 0; j < N; ++j)
         {
            if (j < N - 1)
               os << std::setw(10) << std::setprecision(6)
               << m[i * N + j] << ", ";
            else
               os << std::setw(10) << std::setprecision(6)
               << m[i * N + j];
         }
         os << "]";
      }
      os << "]\n";

      return os;
   }
}