#pragma once

#include <type_traits>

#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Vector<1, T>
   {
      // Class data
      union { T x, r, i, s; };


      // Default constructor
      constexpr
      Vector();


      // Basic Constructors
      constexpr explicit
      Vector(T scalar);


      // Copy Constructor
      constexpr
      Vector(const Vector<1, T>& v);


      // Conversion constructors
      template <typename U>
      constexpr explicit
      Vector(const Vector<1, U>& v);

      template <typename U>
      constexpr explicit
      Vector(const Vector<4, U>& v);

      template <typename U>
      constexpr explicit
      Vector(const Vector<3, U>& v);

      template <typename U>
      constexpr explicit
      Vector(const Vector<2, U>& v);

      template <typename X>
      constexpr
      Vector(X x);


      // Assignment operators
      constexpr
      Vector<1, T>& operator=(T scalar);

      constexpr
      Vector<1, T>& operator=(const Vector<1, T>& other) = default;

      template <typename U>
      constexpr
      Vector<1, T>& operator=(const Vector<1, U>& other);


      // Compound assignment operators
      template <typename U>
      constexpr
      Vector<1, T>& operator+=(const Vector<1, U>& v);

      template <typename U>
      constexpr
      Vector<1, T>& operator-=(const Vector<1, U>& v);

      template <typename U>
      constexpr
      Vector<1, T>& operator*=(const Vector<1, U>& v);

      template <typename U>
      constexpr
      Vector<1, T>& operator*=(U scalar);

      template <typename U>
      constexpr
      Vector<1, T>& operator/=(U scalar);


      inline constexpr explicit
      operator bool() const;


      constexpr
      UInt size() const { return 1; }


      // Element acessing
      constexpr
      T& operator[](std::size_t pos);
      constexpr
      const T& operator[](std::size_t pos) const;

      constexpr
      T& operator()(std::size_t pos) { return (*this)[pos]; }
      constexpr
      const T& operator()(std::size_t pos) const { return (*this)[pos]; }

      constexpr
      T* dataPointer() { return &x; }
      constexpr
      const T* dataPointer() const { return &x; }


      // Conversion operator
      constexpr
      operator T() const { return x; }
   };


   // Nom member operators
   template <typename T>
   inline constexpr
   Vector<1, T> operator+(const Vector<1, T>& va, const Vector<1, T>& vb);

   template <typename T>
   inline constexpr
   Vector<1, T> operator-(const Vector<1, T>& v);

   template <typename T>
   inline constexpr
   Vector<1, T> operator-(const Vector<1, T>& va, const Vector<1, T>& vb);

   template <typename T>
   inline constexpr
   Vector<1, T> operator*(const Vector<1, T>& va, const Vector<1, T>& vb);

   template <typename T>
   inline constexpr
   Vector<1, T> operator*(T scalar, const Vector<1, T>& v);

   template <typename T>
   inline constexpr
   Vector<1, T> operator*(const Vector<1, T>& v, T scalar);

   template <typename T>
   inline constexpr
   Vector<1, T> operator/(const Vector<1, T>& v, T scalar);
}

#include "Neat/Math/Vector/Vector1.inl"