

namespace Neat
{
   // Inner/Dot product
   template <typename T>
   T dotProduct(const Vec<1, T>& va, const Vec<1, T>& vb)
   {
      return va[0] * vb[0];
   }

   template <typename T>
   T dotProduct(const Vec<2, T>& va, const Vec<2, T>& vb)
   {
      return va[0] * vb[0] + va[1] * vb[1];
   }

   template <typename T>
   T dotProduct(const Vec<3, T>& va, const Vec<3, T>& vb)
   {
      return va[0] * vb[0] + va[1] * vb[1] + va[2] * vb[2];
   }

   template <typename T>
   T dotProduct(const Vec<4, T>& va, const Vec<4, T>& vb)
   {
      return
         va[0] * vb[0] + va[1] * vb[1] + va[2] * vb[2] + va[3] * vb[3];
   }

   template <typename T, std::size_t N>
   T innerProduct(const Vec<N, T>& va, const Vec<N, T>& vb)
   {
      return dotProduct(va, vb);
   }

   // Cross product
   template <typename T>
   Vec<3, T> crossProduct(const Vec<3, T>& va, const Vec<3, T>& vb)
   {
      return Vec<3, T>(
         va[1] * vb[2] - va[2] * vb[1],
         va[2] * vb[0] - va[0] * vb[2],
         va[0] * vb[1] - va[1] * vb[0]
         );
   }

   // Norm
   template <typename T>
   T norm(const Vec<1, T>& v)
   {
      return v[0];
   }

   template <typename T>
   T norm(const Vec<2, T>& v)
   {
      return static_cast<T>(std::sqrt(v[0] * v[0] + v[1] * v[1]));
   }

   template <typename T>
   T norm(const Vec<3, T>& v)
   {
      return static_cast<T>(std::sqrt(
         v[0] * v[0] + v[1] * v[1] + v[2] * v[2])
         );
   }

   template <typename T>
   T norm(const Vec<4, T>& v)
   {
      return static_cast<T>(std::sqrt(
         v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3])
         );
   }

   // Normalize
   template <typename T>
   Vec<1, T> normalize(const Vec<1, T>& v)
   {
      return Vec<1, T> v
   }

   template <typename T>
   Vec<2, T> normalize(const Vec<2, T>& v)
   {
      T length = norm(v);

      return Vec<2, T>(v[0] / length, v[1] / length);
   }

   template <typename T>
   Vec<3, T> normalize(const Vec<3, T>& v)
   {
      T length = norm(v);

      return Vec<3, T>(v[0] / length, v[1] / length, v[2] / length);
   }

   template <typename T>
   Vec<4, T> normalize(const Vec<4, T>& v)
   {
      T length = norm(v);

      return Vec<4, T>(
         v[0] / length, v[1] / length, v[2] / length, v[3] / length
         );
   }
}