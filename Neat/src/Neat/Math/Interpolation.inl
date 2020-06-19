

namespace Neat
{
   template <UInt32 N, typename T, typename U>
   inline constexpr Vector<N, T> mix(
      const Vector<N, T>& a, const Vector<N, T>& b, const U& t)
   {
      return
         a * (one<T> - static_cast<T>(t)) + b * static_cast<T>(t);
   }

   template <UInt32 N, typename T, typename U>
   inline constexpr Vector<N, T> quadraticBezier(const Vector<N, T>& a,
      const Vector<N, T>& b, const Vector<N, T>& c, const U& t)
   {
      auto d = mix(a, b, t);
      auto e = mix(b, c, t);
      auto p = mix(d, e, t);

      return p;
   }

   template <UInt32 N, typename T, typename U>
   inline constexpr Vector<N, T> cubicBezier(const Vector<N, T>& a,
      const Vector<N, T>& b, const Vector<N, T>& c, const Vector<N, T>& d,
      const U& t)
   {
      auto e = mix(a, b, t);
      auto f = mix(b, c, t);
      auto g = mix(c, d, t);

      auto h = mix(e, f, t);
      auto i = mix(f, g, t);
      auto p = mix(h, i, t);

      return p;
   }
}