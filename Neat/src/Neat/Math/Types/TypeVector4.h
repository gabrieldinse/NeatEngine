#pragma once

#include <type_traits>

#include "Neat/Math/Types/TypeVectorN.h"


namespace Neat
{
   template <typename T>
   struct Vector<4, T>
   {
      using Type = Vector<4, T>;
      using ValueType = T;


      // Class Data
      union
      {
         struct { T x, y, z, w; };
         struct { T r, g, b, a; };
         struct { T i, j, k, l; };
         struct { T s, t, p, q; };
      };


      // Default constructor
      constexpr
      Vector();


      // Basic Constructors
      constexpr explicit
      Vector(const T& scalar);

      constexpr
      Vector(const T& x, const T& y, const T& z, const T& w);


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
      Vector(const Vector<3, A>& v, const B& scalar);

      template <typename A, typename B, typename C>
      constexpr explicit
      Vector(const Vector<2, A>& v, const B& scalar1, const C& scalar2);

      template <typename A, typename B, typename C, typename D>
      constexpr explicit
      Vector(const Vector<1, A>& v, const B& scalar1, const C& scalar2, const D& scalar3);

      template <typename X, typename Y, typename Z, typename W>
      constexpr
      Vector(X x, Y y, Z z, W w);


      // Assignment operators
      constexpr
      Vector<4, T>& operator=(const Vector<4, T>& other) = default;

      template <typename U>
      constexpr
      Vector<4, T>& operator=(const Vector<4, U>& other);


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
      Vector<4, T>& operator*=(const U& scalar);

      template <typename U>
      constexpr
      Vector<4, T>& operator/=(const U& scalar);


      constexpr explicit
      operator bool() const;


      constexpr
      UInt32 size() const { return 4; }

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
      T* data() { return &x; }
      constexpr
      const T* data() const { return &x; }
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
   Vector<4, T> operator*(const T& scalar, const Vector<4, T>& v);

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(const Vector<4, T>& v, const T& scalar);

   template <typename T>
   inline constexpr
   Vector<4, T> operator/(const Vector<4, T>& v, const T& scalar);


}

#include "Neat/Math/Types/TypeVector4.inl"