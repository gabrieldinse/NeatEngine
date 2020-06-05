#pragma once

#include <type_traits>

#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Vector<3, T>
   {
      // Class Data
      union { T x, r, i, s; };
      union { T y, g, j, t; };
      union { T z, b, k, p; };


      // Default constructor
      constexpr
      Vector();


      // Basic Constructors
      constexpr explicit
      Vector(T scalar);

      constexpr
      Vector(T x, T y, T z);

      // Copy Constructor
      constexpr
      Vector(const Vector<3, T>& v);


      // Conversion constructors
      template <typename U>
      constexpr explicit
      Vector(const Vector<3, U>& v);

      template <typename U>
      constexpr explicit
      Vector(const Vector<4, U>& v);

      template <typename U>
      constexpr explicit
      Vector(const Vector<2, U>& v);

      template <typename U>
      constexpr explicit
      Vector(const Vector<1, U>& v);

      template <typename A, typename B>
      constexpr explicit
      Vector(const Vector<2, A>& v, B scalar1);

      template <typename A, typename B, typename C>
      constexpr explicit
      Vector(const Vector<1, A>& v, B scalar1, C scalar2);

      template <typename X, typename Y, typename Z>
      constexpr
      Vector(X x, Y y, Z z);


      // Assignment operators
      constexpr
      Vector<3, T>& operator=(const Vector<3, T>& other) = default;

      template <typename U>
      constexpr
      Vector<3, T>& operator=(const Vector<3, U>& other);


      // Compound assignment operators
      template <typename U>
      constexpr
      Vector<3, T>& operator+=(const Vector<3, U>& v);

      template <typename U>
      constexpr
      Vector<3, T>& operator-=(const Vector<3, U>& v);

      template <typename U>
      constexpr
      Vector<3, T>& operator*=(const Vector<3, U>& v);

      template <typename U>
      constexpr
      Vector<3, T>& operator*=(const Vector<1, U>& v);

      template <typename U>
      constexpr
      Vector<3, T>& operator*=(U scalar);

      template <typename U>
      constexpr
      Vector<3, T>& operator/=(U scalar);


      inline constexpr explicit
      operator bool() const;


      constexpr
      UInt size() const { return 3; }


      // Element acessingT& operator[](std::size_t pos);
      constexpr
      T& operator[](std::size_t pos);
      constexpr
      const T& operator[](std::size_t pos) const;

      constexpr
      T& operator()(std::size_t pos) { return (*this)[pos]; }
      constexpr
      const T& operator()(std::size_t pos) const { return (*this)[pos]; }

      constexpr
      T* data() { return &x; }
      constexpr
      const T* data() const { return &x; }
   };


   // Nom member operators
   template <typename T>
   inline constexpr
   Vector<3, T> operator+(const Vector<3, T>& va, const Vector<3, T>& vb);

   template <typename T>
   inline constexpr
   Vector<3, T> operator-(const Vector<3, T>& v);

   template <typename T>
   inline constexpr
   Vector<3, T> operator-(const Vector<3, T>& va, const Vector<3, T>& vb);

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Vector<3, T>& va, const Vector<3, T>& vb);

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Vector<3, T>& va, const Vector<1, T>& vb);

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(T scalar, const Vector<3, T>& v);

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Vector<3, T>& v, T scalar);

   template <typename T>
   inline constexpr
      Vector<3, T> operator/(const Vector<3, T>& v, T scalar);
}

#include "Neat/Math/Vector/Vector3.inl"