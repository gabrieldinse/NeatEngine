#include "Neat/Math/VectorOperations.h"


namespace Neat
{
   // Default constructor
   template <typename T>
   inline constexpr
   Vector<2, T>::Vector() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}


   // Basic Constructors
   template <typename T>
   inline constexpr
   Vector<2, T>::Vector(const T& scalar) : x(scalar), y(scalar) {}

   template <typename T>
   inline constexpr
   Vector<2, T>::Vector(const T& x, const T& y) : x(x), y(y) {}


   // Copy Constructor
   template <typename T>
   inline constexpr
   Vector<2, T>::Vector(const Vector<2, T>& v) : x(v.x), y(v.y) {}


   // Conversion constructors
   template <typename T>
   template <typename U>
   inline constexpr
   Vector<2, T>::Vector(const Vector<2, U>& v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

   template <typename T>
   template <typename U>
   inline constexpr
   Vector<2, T>::Vector(const Vector<4, U>& v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

   template <typename T>
   template <typename U>
   inline constexpr
   Vector<2, T>::Vector(const Vector<3, U>& v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

   template <typename T>
   template <typename U>
   inline constexpr
   Vector<2, T>::Vector(const Vector<1, U>& v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(0)) {}

   template <typename T>
   template <typename A, typename B>
   inline constexpr
   Vector<2, T>::Vector(const Vector<1, A>& v, const B& scalar1)
      : x(static_cast<T>(v.x)), y(static_cast<T>(scalar1)) {}

   template <typename T>
   template <typename X, typename Y>
   inline constexpr
   Vector<2, T>::Vector(X x, Y y) : x(static_cast<T>(x)), y(static_cast<T>(y)) {}


   // Assignment operators
   template <typename T>
   template <typename U>
   inline constexpr
   Vector<2, T>& Vector<2, T>::operator=(const Vector<2, U>& other)
   {
      x = other.x;
      y = other.y;

      return *this;
   }


   // Compound assignment operators
   template<typename T>
   template<typename U>
   inline constexpr
   Vector<2, T>& Vector<2, T>::operator+=(const Vector<2, U>& v)
   {
      x += v.x;
      y += v.y;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vector<2, T>& Vector<2, T>::operator-=(const Vector<2, U>& v)
   {
      x -= v.x;
      y -= v.y;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vector<2, T>& Vector<2, T>::operator*=(const Vector<2, U>& v)
   {
      x *= v.x;
      y *= v.y;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vector<2, T>& Vector<2, T>::operator*=(const U& scalar)
   {
      x *= scalar;
      y *= scalar;

      return *this;
   }

   template<typename T>
   template<typename U>
   inline constexpr
   Vector<2, T>& Vector<2, T>::operator/=(const U& scalar)
   {
      x /= scalar;
      y /= scalar;

      return *this;
   }


   template <typename T>
   inline constexpr
   Vector<2, T>::operator bool() const
   {
      return (norm(*this) > static_cast<T>(0));
   }
   

   template<typename T>
   inline  constexpr
   T& Vector<2, T>::operator[](std::size_t pos)
   {
      switch (pos)
      {
         case static_cast<T>(0): return x;
         case 1: return y;
      }

      throw VectorDimensionError();
   }

   template<typename T>
   inline constexpr
   const T& Vector<2, T>::operator[](std::size_t pos) const
   {
      switch (pos)
      {
         case 0: return x;
         case 1: return y;
      }

      throw VectorDimensionError();
   }


   // Non member operators
   template <typename T>
   inline constexpr
      Vector<2, T> operator+(const Vector<2, T>& va, const Vector<2, T>& vb)
   {
      return Vector<2, T>(va) += vb;
   }

   template <typename T>
   inline constexpr
      Vector<2, T> operator-(const Vector<2, T>& v)
   {
      return Vector<2, T>(-v.x, -v.y);
   }

   template <typename T>
   inline constexpr
      Vector<2, T> operator-(const Vector<2, T>& va, const Vector<2, T>& vb)
   {
      return Vector<2, T>(va) -= vb;
   }

   template <typename T>
   inline constexpr
      Vector<2, T> operator*(const Vector<2, T>& va, const Vector<2, T>& vb)
   {
      return Vector<2, T>(va) *= vb;
   }

   template <typename T>
   inline constexpr
      Vector<2, T> operator*(const Vector<2, T>& va, const Vector<1, T>& vb)
   {
      return Vector<2, T>(va) *= vb.x;
   }

   template <typename T>
   inline constexpr
      Vector<2, T> operator*(const Vector<1, T>& va, const Vector<2, T>& vb)
   {
      return Vector<2, T>(vb) *= va.x;
   }

   template <typename T>
   inline constexpr
      Vector<2, T> operator*(const T& scalar, const Vector<2, T>& v)
   {
      return Vector<2, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
      Vector<2, T> operator*(const Vector<2, T>& v, const T& scalar)
   {
      return Vector<2, T>(v) *= scalar;
   }

   template <typename T>
   inline constexpr
      Vector<2, T> operator/(const Vector<2, T>& v, const T& scalar)
   {
      return Vector<2, T>(v) /= scalar;
   }
}