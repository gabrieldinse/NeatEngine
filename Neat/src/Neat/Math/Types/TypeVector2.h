#pragma once

#include <type_traits>

#include "Neat/Math/Types/TypeVectorN.h"
#include "Neat/Core/Log.h"


namespace Neat
{
   template <typename T>
   struct Vector<2, T>
   {
      using Type = Vector<2, T>;
      using ValueType = T;


      // Class data
      union
      {
         struct { T x, y; };
         struct { T r, g; };
         struct { T i, j; };
         struct { T s, t; };
      };
      

      // Default constructor
      constexpr
      Vector();


      // Basic Constructors
      constexpr explicit
      Vector(const T& scalar);

      constexpr
      Vector(const T& x, const T& y);


      // Copy Constructor
      constexpr
      Vector(const Vector<2, T>& v);


      // Conversion constructors
      template <typename U>
      constexpr explicit
      Vector(const Vector<2, U>& v);

      template <typename U>
      constexpr explicit
      Vector(const Vector<4, U>& v);

      template <typename U>
      constexpr explicit
      Vector(const Vector<3, U>& v);

      template <typename U>
      constexpr explicit
      Vector(const Vector<1, U>& v);

      template <typename A, typename B>
      constexpr explicit
      Vector(const Vector<1, A>& v, const B& scalar1);

      template <typename X, typename Y>
      constexpr
      Vector(X x, Y y);


      // Assignment operators
      constexpr
      Vector<2, T>& operator=(const Vector<2, T>& other) = default;

      template <typename U>
      constexpr
      Vector<2, T>& operator=(const Vector<2, U>& other);


      // Compound assignment operators
      template <typename U>
      constexpr
      Vector<2, T>& operator+=(const Vector<2, U>& v);

      template <typename U>
      constexpr
      Vector<2, T>& operator-=(const Vector<2, U>& v);

      template <typename U>
      constexpr
      Vector<2, T>& operator*=(const Vector<2, U>& v);

      template <typename U>
      constexpr
      Vector<2, T>& operator*=(const Vector<1, U>& v);

      template <typename U>
      constexpr
      Vector<2, T>& operator*=(const U& scalar);

      template <typename U>
      constexpr
      Vector<2, T>& operator/=(const U& scalar);


      inline constexpr explicit
      operator bool() const;


      constexpr
      UInt32 size() const { return 2; }


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
   Vector<2, T> operator+(const Vector<2, T>& va, const Vector<2, T>& vb);

   template <typename T>
   inline constexpr
   Vector<2, T> operator-(const Vector<2, T>& v);

   template <typename T>
   inline constexpr
   Vector<2, T> operator-(const Vector<2, T>& va, const Vector<2, T>& vb);

   template <typename T>
   inline constexpr
   Vector<2, T> operator*(const Vector<2, T>& va, const Vector<2, T>& vb);

   template <typename T>
   inline constexpr
   Vector<2, T> operator*(const Vector<2, T>& va, const Vector<1, T>& vb);

   template <typename T>
   inline constexpr
   Vector<2, T> operator*(const T& scalar, const Vector<2, T>& v);

   template <typename T>
   inline constexpr
   Vector<2, T> operator*(const Vector<2, T>& v, const T& scalar);

   template <typename T>
   inline constexpr
   Vector<2, T> operator/(const Vector<2, T>& v, const T& scalar);
}

#include "Neat/Math/Types/TypeVector2.inl"