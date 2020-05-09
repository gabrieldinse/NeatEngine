#pragma once

#include <type_traits>

#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Vec<3, T>
   {
      // Class Data
      union { T x, r, i, s; };
      union { T y, g, j, t; };
      union { T z, b, k, p; };


      // Default constructor
      constexpr
      Vec();


      // Basic Constructors
      constexpr explicit
      Vec(T scalar);

      constexpr
      Vec(T x, T y, T z);

      // Copy Constructor
      constexpr
      Vec(const Vec<3, T>& v);


      // Conversion constructors
      template <typename U>
      constexpr explicit
      Vec(const Vec<3, U>& v);

      template <typename U>
      constexpr explicit
      Vec(const Vec<4, U>& v);

      template <typename U>
      constexpr explicit
      Vec(const Vec<2, U>& v);

      template <typename U>
      constexpr explicit
      Vec(const Vec<1, U>& v);

      template <typename A, typename B>
      constexpr explicit
      Vec(const Vec<2, A>& v, B scalar1);

      template <typename A, typename B, typename C>
      constexpr explicit
      Vec(const Vec<1, A>& v, B scalar1, C scalar2);

      template <typename X, typename Y, typename Z>
      constexpr
      Vec(X x, Y y, Z z);


      // Assignment operators
      constexpr
      Vec<3, T>& operator=(const Vec<4, T>& other);

      constexpr
      Vec<3, T>& operator=(const Vec<3, T>& other);

      constexpr
      Vec<3, T>& operator=(const Vec<2, T>& other);

      constexpr
      Vec<3, T>& operator=(const Vec<1, T>& other);


      // Compound assignment operators
      template <typename U>
      constexpr
      Vec<3, T>& operator+=(const Vec<3, U>& v);

      template <typename U>
      constexpr
      Vec<3, T>& operator-=(const Vec<3, U>& v);

      template <typename U>
      constexpr
      Vec<3, T>& operator*=(const Vec<3, U>& v);

      template <typename U>
      constexpr
      Vec<3, T>& operator*=(const Vec<1, U>& v);

      template <typename U>
      constexpr
      Vec<3, T>& operator*=(U scalar);

      template <typename U>
      constexpr
      Vec<3, T>& operator/=(U scalar);


      inline constexpr operator Bool() const;


      constexpr SizeType size() const
      {
         return std::extent<decltype(this->data)>::value;
      }


      // Element acessingT& operator[](SizeType pos);
      const T& operator[](SizeType pos) const;
      T& operator[](SizeType pos);

      T& operator()(SizeType pos) { return (*this)[pos]; }
      const T& operator()(SizeType pos) const { return (*this)[pos]; }

      T* dataPointer() { return &this->x; }
      const T* dataPointer() const { return &this->x; }
   };


   // Nom member operators
   template <typename T>
   inline constexpr
   Vec<3, T> operator+(const Vec<3, T>& va, const Vec<3, T>& vb);

   template <typename T>
   inline constexpr
   Vec<3, T> operator-(const Vec<3, T>& v);

   template <typename T>
   inline constexpr
   Vec<3, T> operator-(const Vec<3, T>& va, const Vec<3, T>& vb);

   template <typename T>
   inline constexpr
   Vec<3, T> operator*(const Vec<3, T>& va, const Vec<3, T>& vb);

   template <typename T>
   inline constexpr
   Vec<3, T> operator*(const Vec<3, T>& va, const Vec<1, T>& vb);

   template <typename T>
   inline constexpr
   Vec<3, T> operator*(T scalar, const Vec<3, T>& v);

   template <typename T>
   inline constexpr
   Vec<3, T> operator*(const Vec<3, T>& v, T scalar);

   template <typename T>
   inline constexpr
      Vec<3, T> operator/(const Vec<3, T>& v, T scalar);
}

#include "Neat/Math/Vector/Vector3.inl"