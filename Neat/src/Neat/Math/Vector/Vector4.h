#pragma once

#include <type_traits>

#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Vec<4, T>
   {
      // Class Data
      union { T x, r, i, s; };
      union { T y, g, j, t; };
      union { T z, b, k, p; };
      union { T w, a, l, q; };


      // Default constructor
      constexpr
      Vec();


      // Basic Constructors
      constexpr explicit
      Vec(T scalar);

      constexpr
      Vec(T x, T y, T z, T w);


      // Copy Constructor
      constexpr
      Vec(const Vec<4, T>& v);


      // Conversion constructors
      template <typename U>
      constexpr explicit
      Vec(const Vec<4, U>& v);
      
      template <typename U>
      constexpr explicit
      Vec(const Vec<3, U>& v);

      template <typename U>
      constexpr explicit
      Vec(const Vec<2, U>& v);

      template <typename U>
      constexpr explicit
       Vec(const Vec<1, U>& v);

      template <typename A, typename B>
      constexpr explicit
      Vec(const Vec<3, A>& v, B scalar);

      template <typename A, typename B, typename C>
      constexpr explicit
      Vec(const Vec<2, A>& v, B scalar1, C scalar2);

      template <typename A, typename B, typename C, typename D>
      constexpr explicit
      Vec(const Vec<1, A>& v, B scalar1, C scalar2, D scalar3);

      template <typename X, typename Y, typename Z, typename W>
      constexpr
      Vec(X x, Y y, Z z, W w);


      // Assignment operators
      constexpr
      Vec<4, T>& operator=(const Vec<4, T>& other);

      constexpr
      Vec<4, T>& operator=(const Vec<3, T>& other);

      constexpr
      Vec<4, T>& operator=(const Vec<2, T>& other);

      constexpr
      Vec<4, T>& operator=(const Vec<1, T>& other);


      // Compound assignment operators
      template <typename U>
      constexpr
      Vec<4, T>& operator+=(const Vec<4, U>& v);

      template <typename U>
      constexpr
      Vec<4, T>& operator-=(const Vec<4, U>& v);

      template <typename U>
      constexpr
      Vec<4, T>& operator*=(const Vec<4, U>& v);

      template <typename U>
      constexpr
      Vec<4, T>& operator*=(const Vec<1, U>& v);

      template <typename U>
      constexpr
      Vec<4, T>& operator*=(U scalar);

      template <typename U>
      constexpr
      Vec<4, T>& operator/=(U scalar);


      constexpr explicit
      operator Bool() const;


      constexpr
      SizeType size() const
      {
         return std::extent<decltype(this->data)>::value;
      }


      // Element acessing
      constexpr
      T& operator[](SizeType pos);
      constexpr
      const T& operator[](SizeType pos) const;

      constexpr
      T& operator()(SizeType pos) { return (*this)[pos]; }
      constexpr
      const T& operator()(SizeType pos) const { return (*this)[pos]; }

      constexpr
      T* dataPointer() { return &this->x; }
      constexpr
      const T* dataPointer() const { return &this->x; }
   };


   // Nom member operators
   template <typename T>
   inline constexpr
   Vec<4, T> operator+(const Vec<4, T>& va, const Vec<4, T>& vb);

   template <typename T>
   inline constexpr
   Vec<4, T> operator-(const Vec<4, T>& v);

   template <typename T>
   inline constexpr
   Vec<4, T> operator-(const Vec<4, T>& va, const Vec<4, T>& vb);

   template <typename T>
   inline constexpr
   Vec<4, T> operator*(const Vec<4, T>& va, const Vec<4, T>& vb);

   template <typename T>
   inline constexpr
   Vec<4, T> operator*(const Vec<4, T>& va, const Vec<1, T>& vb);

   template <typename T>
   inline constexpr
   Vec<4, T> operator*(const Vec<1, T>& va, const Vec<4, T>& vb);

   template <typename T>
   inline constexpr
   Vec<4, T> operator*(T scalar, const Vec<4, T>& v);

   template <typename T>
   inline constexpr
   Vec<4, T> operator*(const Vec<4, T>& v, T scalar);

   template <typename T>
   inline constexpr
   Vec<4, T> operator/(const Vec<4, T>& v, T scalar);


}

#include "Neat/Math/Vector/Vector4.inl"