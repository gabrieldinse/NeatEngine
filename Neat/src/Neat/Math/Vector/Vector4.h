#pragma once

#include <type_traits>

#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Vector<4, T>
   {
      // Class Data
      union { T x, r, i, s; };
      union { T y, g, j, t; };
      union { T z, b, k, p; };
      union { T w, a, l, q; };


      // Default constructor
      constexpr
      Vector();


      // Basic Constructors
      constexpr explicit
      Vector(T scalar);

      constexpr
      Vector(T x, T y, T z, T w);


      // Copy Constructor
      constexpr
      Vector(const Vector<4, T>& v);


      // Conversion constructors
      template <typename U>
      constexpr explicit
      Vector(const Vector<4, U>& v);
      
      template <typename U>
      constexpr explicit
      Vector(const Vector<3, U>& v);

      template <typename U>
      constexpr explicit
      Vector(const Vector<2, U>& v);

      template <typename U>
      constexpr explicit
       Vector(const Vector<1, U>& v);

      template <typename A, typename B>
      constexpr explicit
      Vector(const Vector<3, A>& v, B scalar);

      template <typename A, typename B, typename C>
      constexpr explicit
      Vector(const Vector<2, A>& v, B scalar1, C scalar2);

      template <typename A, typename B, typename C, typename D>
      constexpr explicit
      Vector(const Vector<1, A>& v, B scalar1, C scalar2, D scalar3);

      template <typename X, typename Y, typename Z, typename W>
      constexpr
      Vector(X x, Y y, Z z, W w);


      // Assignment operators
      constexpr
      Vector<4, T>& operator=(const Vector<4, T>& other);

      constexpr
      Vector<4, T>& operator=(const Vector<3, T>& other);

      constexpr
      Vector<4, T>& operator=(const Vector<2, T>& other);

      constexpr
      Vector<4, T>& operator=(const Vector<1, T>& other);


      // Compound assignment operators
      template <typename U>
      constexpr
      Vector<4, T>& operator+=(const Vector<4, U>& v);

      template <typename U>
      constexpr
      Vector<4, T>& operator-=(const Vector<4, U>& v);

      template <typename U>
      constexpr
      Vector<4, T>& operator*=(const Vector<4, U>& v);

      template <typename U>
      constexpr
      Vector<4, T>& operator*=(const Vector<1, U>& v);

      template <typename U>
      constexpr
      Vector<4, T>& operator*=(U scalar);

      template <typename U>
      constexpr
      Vector<4, T>& operator/=(U scalar);


      constexpr explicit
      operator bool() const;


      constexpr
      std::size_t size() const
      {
         return std::extent<decltype(m_data)>::value;
      }


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
   };


   // Nom member operators
   template <typename T>
   inline constexpr
   Vector<4, T> operator+(const Vector<4, T>& va, const Vector<4, T>& vb);

   template <typename T>
   inline constexpr
   Vector<4, T> operator-(const Vector<4, T>& v);

   template <typename T>
   inline constexpr
   Vector<4, T> operator-(const Vector<4, T>& va, const Vector<4, T>& vb);

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(const Vector<4, T>& va, const Vector<4, T>& vb);

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(const Vector<4, T>& va, const Vector<1, T>& vb);

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(const Vector<1, T>& va, const Vector<4, T>& vb);

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(T scalar, const Vector<4, T>& v);

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(const Vector<4, T>& v, T scalar);

   template <typename T>
   inline constexpr
   Vector<4, T> operator/(const Vector<4, T>& v, T scalar);


}

#include "Neat/Math/Vector/Vector4.inl"