#include "Neat/Math/VectorOperations.h"


namespace Neat
{
   // Default constructor
   template <typename T>
   constexpr
   Vector<3, T>::Vector() :
      x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)) {}


   // Basic Constructors
   template <typename T>
   constexpr
   Vector<3, T>::Vector(T scalar) : x(scalar), y(scalar), z(scalar) {}

   template <typename T>
   constexpr
   Vector<3, T>::Vector(T x, T y, T z) : x(x), y(y), z(z) {}

   // Copy Constructor
   template <typename T>
   constexpr
   Vector<3, T>::Vector(const Vector<3, T>& v) : x(v.x), y(v.y), z(v.z) {}


   // Conversion constructors
   template <typename T>
   template <typename U>
   constexpr
   Vector<3, T>::Vector(const Vector<3, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(v.z)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vector<3, T>::Vector(const Vector<4, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(v.z)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vector<3, T>::Vector(const Vector<2, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(0)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vector<3, T>::Vector(const Vector<1, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(0))
      , z(static_cast<T>(0)) {}

   template <typename T>
   template <typename A, typename B>
   constexpr
   Vector<3, T>::Vector(const Vector<2, A>& v, B scalar1)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(scalar1)) {}

   template <typename T>
   template <typename A, typename B, typename C>
   constexpr
   Vector<3, T>::Vector(const Vector<1, A>& v, B scalar1, C scalar2)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(scalar1))
      , z(static_cast<T>(scalar2)) {}

   template <typename T>
   template <typename X, typename Y, typename Z>
   constexpr
   Vector<3, T>::Vector(X x, Y y, Z z)
      : x(static_cast<T>(x))
      , y(static_cast<T>(y))
      , z(static_cast<T>(z)) {}


   // Assignment operators

   template <typename T>
   template <typename U>
   constexpr
   Vector<3, T>& Vector<3, T>::operator=(const Vector<3, U>& other)
   {
      x = other.x;
      y = other.y;
      z = other.z;

      return *this;
   }


   // Compound assigment operators
   template<typename T>
   template<typename U>
   inline constexpr Vector<3, T>& Vector<3, T>::operator+=(const Vector<3, U>& v)
   {
      x += v.x;
      y += v.y;
      z += v.z;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vector<3, T>& Vector<3, T>::operator-=(const Vector<3, U>& v)
   {
      x -= v.x;
      y -= v.y;
      z -= v.z;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vector<3, T>& Vector<3, T>::operator*=(const Vector<3, U>& v)
   {
      x *= v.x;
      y *= v.y;
      z *= v.z;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vector<3, T>& Vector<3, T>::operator*=(U scalar)
   {
      x *= scalar;
      y *= scalar;
      z *= scalar;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vector<3, T>& Vector<3, T>::operator/=(U scalar)
   {
      x /= scalar;
      y /= scalar;
      z /= scalar;

      return *this;
   }


   template <typename T>
   inline constexpr
      Vector<3, T>::operator bool() const
   {
      return (norm(*this) > static_cast<T>(0));
   }


   template <typename T>
   inline constexpr
   T& Vector<3, T>::operator[](std::size_t pos)
   {
      switch (pos)
      {
         case 0: return x;
         case 1: return y;
         case 2: return z;
      }

      throw VecDimensionError();
   }

   template <typename T>
   inline constexpr
   const T& Vector<3, T>::operator[](std::size_t pos) const
   {
      switch (pos)
      {
         case 0: return x;
         case 1: return y;
         case 2: return z;
      }

      throw VecDimensionError();
   }


   // Non member operators
   template <typename T>
   inline constexpr
   Vector<3, T> operator+(const Vector<3, T>& va, const Vector<3, T>& vb)
   {
      return Vector<3, T>(va) += vb;
   }

   template <typename T>
   inline constexpr
   Vector<3, T> operator-(const Vector<3, T>& v)
   {
      return Vector<3, T>(-v.x, -v.y, -v.z);
   }

   template <typename T>
   inline constexpr
   Vector<3, T> operator-(const Vector<3, T>& va, const Vector<3, T>& vb)
   {
      return Vector<3, T>(va) -= vb;
   }

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Vector<3, T>& va, const Vector<3, T>& vb)
   {
      return Vector<3, T>(va) *= vb;
   }

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Vector<3, T>& va, const Vector<1, T>& vb)
   {
      return Vector<3, T>(va) *= vb.x;
   }

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Vector<1, T>& va, const Vector<3, T>& vb)
   {
      return Vector<3, T>(vb) *= va.x;
   }

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(T scalar, const Vector<3, T>& v)
   {
      return Vector<3, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Vector<3, T>& v, T scalar)
   {
      return Vector<3, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
   Vector<3, T> operator/(const Vector<3, T>& v, T scalar)
   {
      return Vector<3, T>(v) /= scalar;
   }
}