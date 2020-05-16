#include "Neat/Math/VectorOperations.h"


namespace Neat
{
   // Default constructor
   template <typename T>
   constexpr
   Vec<3, T>::Vec() :
      x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)) {}


   // Basic Constructors
   template <typename T>
   constexpr
   Vec<3, T>::Vec(T scalar) : x(scalar), y(scalar), z(scalar) {}

   template <typename T>
   constexpr
   Vec<3, T>::Vec(T x, T y, T z) : x(x), y(y), z(z) {}

   // Copy Constructor
   template <typename T>
   constexpr
   Vec<3, T>::Vec(const Vec<3, T>& v) : x(v.x), y(v.y), z(v.z) {}


   // Conversion constructors
   template <typename T>
   template <typename U>
   constexpr
   Vec<3, T>::Vec(const Vec<3, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(v.z)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vec<3, T>::Vec(const Vec<4, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(v.z)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vec<3, T>::Vec(const Vec<2, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(0)) {}

   template <typename T>
   template <typename U>
   constexpr
   Vec<3, T>::Vec(const Vec<1, U>& v)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(0))
      , z(static_cast<T>(0)) {}

   template <typename T>
   template <typename A, typename B>
   constexpr
   Vec<3, T>::Vec(const Vec<2, A>& v, B scalar1)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(v.y))
      , z(static_cast<T>(scalar1)) {}

   template <typename T>
   template <typename A, typename B, typename C>
   constexpr
   Vec<3, T>::Vec(const Vec<1, A>& v, B scalar1, C scalar2)
      : x(static_cast<T>(v.x))
      , y(static_cast<T>(scalar1))
      , z(static_cast<T>(scalar2)) {}

   template <typename T>
   template <typename X, typename Y, typename Z>
   constexpr
   Vec<3, T>::Vec(X x, Y y, Z z)
      : x(static_cast<T>(x))
      , y(static_cast<T>(y))
      , z(static_cast<T>(z)) {}


   // Assignment operators
   template <typename T>
   constexpr
   Vec<3, T>& Vec<3, T>::operator=(const Vec<4, T>& other)
   {
      x = other.x;
      y = other.y;
      z = other.z;

      return *this;
   }

   template <typename T>
   constexpr
   Vec<3, T>& Vec<3, T>::operator=(const Vec<3, T>& other)
   {
      x = other.x;
      y = other.y;
      z = other.z;

      return *this;
   }

   template <typename T>
   constexpr
   Vec<3, T>& Vec<3, T>::operator=(const Vec<2, T>& other)
   {
      x = other.x;
      y = other.y;
      z = static_cast<T>(0);

      return *this;
   }

   template <typename T>
   constexpr
   Vec<3, T>& Vec<3, T>::operator=(const Vec<1, T>& other)
   {
      x = other.x;
      y = static_cast<T>(0);
      z = static_cast<T>(0);

      return *this;
   }


   // Compound assigment operators
   template<typename T>
   template<typename U>
   inline constexpr Vec<3, T>& Vec<3, T>::operator+=(const Vec<3, U>& v)
   {
      x += v.x;
      y += v.y;
      z += v.z;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vec<3, T>& Vec<3, T>::operator-=(const Vec<3, U>& v)
   {
      x -= v.x;
      y -= v.y;
      z -= v.z;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vec<3, T>& Vec<3, T>::operator*=(const Vec<3, U>& v)
   {
      x *= v.x;
      y *= v.y;
      z *= v.z;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vec<3, T>& Vec<3, T>::operator*=(U scalar)
   {
      x *= scalar;
      y *= scalar;
      z *= scalar;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr Vec<3, T>& Vec<3, T>::operator/=(U scalar)
   {
      x /= scalar;
      y /= scalar;
      z /= scalar;

      return *this;
   }


   template <typename T>
   inline constexpr
      Vec<3, T>::operator bool() const
   {
      return (norm(*this) > static_cast<T>(0));
   }


   template <typename T>
   inline constexpr
   T& Vec<3, T>::operator[](std::size_t pos)
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
   const T& Vec<3, T>::operator[](std::size_t pos) const
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
   Vec<3, T> operator+(const Vec<3, T>& va, const Vec<3, T>& vb)
   {
      return Vec<3, T>(va) += vb;
   }

   template <typename T>
   inline constexpr
   Vec<3, T> operator-(const Vec<3, T>& v)
   {
      return Vec<3, T>(-v.x, -v.y, -v.z);
   }

   template <typename T>
   inline constexpr
   Vec<3, T> operator-(const Vec<3, T>& va, const Vec<3, T>& vb)
   {
      return Vec<3, T>(va) -= vb;
   }

   template <typename T>
   inline constexpr
   Vec<3, T> operator*(const Vec<3, T>& va, const Vec<3, T>& vb)
   {
      return Vec<3, T>(va) *= vb;
   }

   template <typename T>
   inline constexpr
   Vec<3, T> operator*(const Vec<3, T>& va, const Vec<1, T>& vb)
   {
      return Vec<3, T>(va) *= vb.x;
   }

   template <typename T>
   inline constexpr
   Vec<3, T> operator*(const Vec<1, T>& va, const Vec<3, T>& vb)
   {
      return Vec<3, T>(vb) *= va.x;
   }

   template <typename T>
   inline constexpr
   Vec<3, T> operator*(T scalar, const Vec<3, T>& v)
   {
      return Vec<3, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
   Vec<3, T> operator*(const Vec<3, T>& v, T scalar)
   {
      return Vec<3, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
   Vec<3, T> operator/(const Vec<3, T>& v, T scalar)
   {
      return Vec<3, T>(v) /= scalar;
   }
}