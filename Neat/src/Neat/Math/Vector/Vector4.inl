#include "Neat/Math/VectorOperations.h"
#include "Vector4.h"


namespace Neat
{
   // Default constructor
   template <typename T>
   constexpr
   Vector<4, T>::Vector()
      : x(static_cast<T>(0))
      , y(static_cast<T>(0))
      , z(static_cast<T>(0))
      , w(static_cast<T>(0)) {}


   // Basic Constructors
   template <typename T>
   constexpr
   Vector<4, T>::Vector(T scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}

   template <typename T>
   constexpr
   Vector<4, T>::Vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}


   // Copy Constructor
   template <typename T>
   constexpr
   Vector<4, T>::Vector(const Vector<4, T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}


   // Conversion constructors
   template <typename T>
   template <typename U>
   constexpr
   Vector<4, T>::Vector(const Vector<4, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(v.z))
      , w(static_cast<T>(v.w)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vector<4, T>::Vector(const Vector<3, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(v.z))
      , w(static_cast<T>(0)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vector<4, T>::Vector(const Vector<2, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(0))
      , w(static_cast<T>(0)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vector<4, T>::Vector(const Vector<1, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(0))
      , z(static_cast<T>(0))
      , w(static_cast<T>(0)) {}

   template <typename T>
   template <typename A, typename B>
   constexpr
   Vector<4, T>::Vector(const Vector<3, A>& v, B scalar)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(v.z))
      , w(static_cast<T>(scalar)) {}

   template <typename T>
   template <typename A, typename B, typename C>
   constexpr
   Vector<4, T>::Vector(const Vector<2, A>& v, B scalar1, C scalar2)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(scalar1))
      , w(static_cast<T>(scalar2)) {}

   template <typename T>
   template <typename A, typename B, typename C, typename D>
   constexpr
   Vector<4, T>::Vector(const Vector<1, A>& v, B scalar1, C scalar2, D scalar3)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(scalar1))
      , z(static_cast<T>(scalar2))
      , w(static_cast<T>(scalar3)) {}

   template <typename T>
   template <typename X, typename Y, typename Z, typename W>
   constexpr
   Vector<4, T>::Vector(X x, Y y, Z z, W w)
      : x(static_cast<T>(x))
      , y(static_cast<T>(y))
      , z(static_cast<T>(z))
      , w(static_cast<T>(w)) {}


   // Assignment operators
   template <typename T>
   template <typename U>
   constexpr
   Vector<4, T>& Vector<4, T>::operator=(const Vector<4, U>& other)
   {
      x = other.x;
      y = other.y;
      z = other.z;
      w = other.w;

      return *this;
   }


   // Compound assigment operators
   template<typename T>
   template<typename U>
   inline constexpr
   Vector<4, T>& Vector<4, T>::operator+=(const Vector<4, U>& v)
   {
      x += v.x;
      y += v.y;
      z += v.z;
      w += v.w;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vector<4, T>& Vector<4, T>::operator-=(const Vector<4, U>& v)
   {
      x -= v.x;
      y -= v.y;
      z -= v.z;
      w -= v.w;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vector<4, T>& Vector<4, T>::operator*=(const Vector<4, U>& v)
   {
      x *= v.x;
      y *= v.y;
      z *= v.z;
      w *= v.w;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vector<4, T>& Vector<4, T>::operator*=(U scalar)
   {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      w *= scalar;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vector<4, T>& Vector<4, T>::operator/=(U scalar)
   {
      x /= static_cast<T>(scalar);
      y /= static_cast<T>(scalar);
      z /= static_cast<T>(scalar);
      w /= static_cast<T>(scalar);

      return *this;
   }


   template <typename T>
   inline constexpr
   Vector<4, T>::operator bool() const
   {
      return (norm(*this) > static_cast<T>(0));
   }


   template<typename T>
   inline constexpr
   T& Vector<4, T>::operator[](std::size_t pos)
   {
      switch (pos)
      {
         case 0: return x;
         case 1: return y;
         case 2: return z;
         case 3: return w;
      }

      throw VecDimensionError();
   }

   template<typename T>
   inline constexpr
   const T& Vector<4, T>::operator[](std::size_t pos) const
   {
      switch (pos)
      {
         case 0: return x;
         case 1: return y;
         case 2: return z;
         case 3: return w;
      }

      throw VecDimensionError();
   }


   // Non member operators
   template <typename T>
   inline constexpr
   Vector<4, T> operator+(const Vector<4, T>& va, const Vector<4, T>& vb)
   {
      return Vector<4, T>(va) += vb;
   }

   template <typename T>
   inline constexpr
   Vector<4, T> operator-(const Vector<4, T>& v)
   {
      return Vector<4, T>(-v.x, -v.y, -v.z, -v.w);
   }

   template <typename T>
   inline constexpr
   Vector<4, T> operator-(const Vector<4, T>& va, const Vector<4, T>& vb)
   {
      return Vector<4, T>(va) -= vb;
   }

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(const Vector<4, T>& va, const Vector<4, T>& vb)
   {
      return Vector<4, T>(va) *= vb;
   }

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(const Vector<4, T>& va, const Vector<1, T>& vb)
   {
      return Vector<4, T>(va) *= vb.x;
   }

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(const Vector<1, T>& va, const Vector<4, T>& vb)
   {
      return Vector<4, T>(vb) *= va.x;
   }

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(T scalar, const Vector<4, T>& v)
   {
      return Vector<4, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
      Vector<4, T> operator*(const Vector<4, T>& v, T scalar)
   {
      return Vector<4, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
      Vector<4, T> operator/(const Vector<4, T>& v, T scalar)
   {
      return Vector<4, T>(v) /= scalar;
   }
}