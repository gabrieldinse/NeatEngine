#pragma once

#include <type_traits>

#include "Neat/Math/Types/TypeVectorN.h"


namespace Neat
{
   template <typename T>
   struct Vector<3, T>
   {
      using Type = Vector<3, T>;
      using ValueType = T;


      // Class Data
      union
      {
         struct { T x, y, z; };
         struct { T r, g, b; };
         struct { T i, j, k; };
         struct { T s, t, p; };
      };


      // Default constructor
      constexpr
      Vector();


      // Basic Constructors
      constexpr explicit
      Vector(const T& scalar);

      constexpr
      Vector(const T& x, const T& y, const T& z);

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
      Vector(const Vector<2, A>& v, const B& scalar1);

      template <typename A, typename B, typename C>
      constexpr explicit
      Vector(const Vector<1, A>& v, const B& scalar1, const C& scalar2);

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
      Vector<3, T>& operator*=(const U& scalar);

      template <typename U>
      constexpr
      Vector<3, T>& operator/=(const U& scalar);


      inline constexpr explicit
      operator bool() const;


      constexpr
      UInt32 size() const { return 3; }


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
   Vector<3, T> operator*(const T& scalar, const Vector<3, T>& v);

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Vector<3, T>& v, const T& scalar);

   template <typename T>
   inline constexpr
      Vector<3, T> operator/(const Vector<3, T>& v, const T& scalar);
}

#include "Neat/Math/Types/TypeVector3.inl"