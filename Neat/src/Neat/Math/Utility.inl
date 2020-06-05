

namespace Neat
{
   template<UInt N, typename T, typename U>
   Vector<N, T> linearInterpolation(
      const Vector<N, T>& a, const Vector<N, T>& b, U t)
   {
      return
         a * (static_cast<T>(1) - static_cast<T>(t)) + b * static_cast<T>(t);
   }

   template<UInt N, typename T, typename U>
   Vector<N, T> quadraticBezier(const Vector<N, T>& a, const Vector<N, T>& b,
      const Vector<N, T>& c, U t)
   {
      auto d = linearInterpolation(a, b, t);
      auto e = linearInterpolation(b, c, t);
      auto p = linearInterpolation(d, e, t);

      return p;
   }

   template<UInt N, typename T, typename U>
   Vector<N, T> cubicBezier(const Vector<N, T>& a, const Vector<N, T>& b,
      const Vector<N, T>& c, const Vector<N, T>& d, U t)
   {
      auto e = linearInterpolation(a, b, t);
      auto f = linearInterpolation(b, c, t);
      auto g = linearInterpolation(c, d, t);

      auto h = linearInterpolation(e, f, t);
      auto i = linearInterpolation(f, g, t);
      auto p = linearInterpolation(h, i, t);

      return p;
   }
}
