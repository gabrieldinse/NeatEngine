

namespace Neat
{
   template <UInt32 N, typename T>
   Vector<N, T> reflect(const Vector<N, T>& v, const Vector<N, T>& normal)
   {
      return v - two<T> * dot(v, normal) * normal;
   }

   // Refract
   template <UInt32 N, typename T>
   Vector<N, T> refract(const Vector<N, T>& v, const Vector<N, T>& normal,
      const T& eta)
   {
      T const d = dot(normal, v);
      T const k = one<T> -eta * eta * (one<T> -d * d);

      Vector<N, T> const result = (k >= zero<T>)
         ? eta * v - (eta * d + static_cast<T>(std::sqrt(k))) * normal
         : Vector<N, T>(0);

      return result;
   }
}