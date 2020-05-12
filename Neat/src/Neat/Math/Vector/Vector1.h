#pragma once

#include <type_traits>

#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Vec<1, T>
   {
      // Class data
      union { T x, r, i, s; };


      // Default constructor
      constexpr
      Vec();


      // Basic Constructors
      constexpr explicit
      Vec(T scalar);


      // Copy Constructor
      constexpr
      Vec(const Vec<1, T>& v);


      // Conversion constructors
      template <typename U>
      constexpr explicit
      Vec(const Vec<1, U>& v);

      template <typename U>
      constexpr explicit
      Vec(const Vec<4, U>& v);

      template <typename U>
      constexpr explicit
      Vec(const Vec<3, U>& v);

      template <typename U>
      constexpr explicit
      Vec(const Vec<2, U>& v);

      template <typename X>
      constexpr
      Vec(X x);


      // Assignment operators
      constexpr
      Vec<1, T>& operator=(T scalar);

      constexpr
      Vec<1, T>& operator=(const Vec<4, T>& other);

      constexpr
      Vec<1, T>& operator=(const Vec<3, T>& other);

      constexpr
      Vec<1, T>& operator=(const Vec<2, T>& other);

      constexpr
      Vec<1, T>& operator=(const Vec<1, T>& other);


      // Compound assignment operators
      template <typename U>
      constexpr
      Vec<1, T>& operator+=(const Vec<1, U>& v);

      template <typename U>
      constexpr
      Vec<1, T>& operator-=(const Vec<1, U>& v);

      template <typename U>
      constexpr
      Vec<1, T>& operator*=(const Vec<1, U>& v);

      template <typename U>
      constexpr
      Vec<1, T>& operator*=(U scalar);

      template <typename U>
      constexpr
      Vec<1, T>& operator/=(U scalar);


      inline constexpr explicit
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


      // Conversion operator
      constexpr
      operator T() const { return this->x; }
   };


   // Nom member operators
   template <typename T>
   inline constexpr
   Vec<1, T> operator+(const Vec<1, T>& va, const Vec<1, T>& vb);

   template <typename T>
   inline constexpr
   Vec<1, T> operator-(const Vec<1, T>& v);

   template <typename T>
   inline constexpr
   Vec<1, T> operator-(const Vec<1, T>& va, const Vec<1, T>& vb);

   template <typename T>
   inline constexpr
   Vec<1, T> operator*(const Vec<1, T>& va, const Vec<1, T>& vb);

   template <typename T>
   inline constexpr
   Vec<1, T> operator*(T scalar, const Vec<1, T>& v);

   template <typename T>
   inline constexpr
   Vec<1, T> operator*(const Vec<1, T>& v, T scalar);

   template <typename T>
   inline constexpr
   Vec<1, T> operator/(const Vec<1, T>& v, T scalar);
}

#include "Neat/Math/Vector/Vector1.inl"