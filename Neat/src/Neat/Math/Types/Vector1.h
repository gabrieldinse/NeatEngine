#pragma once

#include <cmath>

#include "Neat/Math/Types/TypeVectorN.h"


namespace Neat
{
   template <typename T>
   struct Vector<1, T>
   {
      using Type = Vector<1, T>;
      using ValueType = T;


      // Class data
      union { T x, r, i, s; };


      // Default constructor
      constexpr Vector();

      // Basic Constructors
      constexpr explicit Vector(const T& scalar);

      // Copy Constructor
      constexpr Vector(const Vector<1, T>& v);

      // Conversion constructors
      template <typename U>
      constexpr explicit Vector(const Vector<1, U>& v);
      template <typename U>
      constexpr explicit Vector(const Vector<4, U>& v);
      template <typename U>
      constexpr explicit Vector(const Vector<3, U>& v);
      template <typename U>
      constexpr explicit Vector(const Vector<2, U>& v);
      template <typename X>
      constexpr Vector(const X& x);

      // Assignment operators
      constexpr Vector<1, T>& operator=(const T& scalar);
      constexpr Vector<1, T>& operator=(const Vector<1, T>& other) = default;
      template <typename U>
      constexpr Vector<1, T>& operator=(const Vector<1, U>& other);

      // Compound assignment operators
      template <typename U>
      constexpr Vector<1, T>& operator+=(const Vector<1, U>& v);
      template <typename U>
      constexpr Vector<1, T>& operator-=(const Vector<1, U>& v);
      template <typename U>
      constexpr Vector<1, T>& operator*=(const Vector<1, U>& v);
      template <typename U>
      constexpr Vector<1, T>& operator*=(const U& scalar);
      template <typename U>
      constexpr Vector<1, T>& operator/=(const U& scalar);

      // Explicit conversion operators
      constexpr explicit operator T() const { return x; }
      inline constexpr explicit operator bool() const { return (std::fabs(x) > zero<T>); }

      // Element acessing
      constexpr T& operator[](UInt32 pos);
      constexpr const T& operator[](UInt32 pos) const;
      constexpr T& operator()(UInt32 pos) { return (*this)[pos]; }
      constexpr const T& operator()(UInt32 pos) const { return (*this)[pos]; }
      constexpr T* dataPointer() { return &x; }
      constexpr const T* dataPointer() const { return &x; }

      // Static member variables
      static constexpr UInt32 size() { return 1; }
      static constexpr UInt32 length() { return size(); }
   };


   // Predefined types
   using Vector1 = Vector<1, float>;
   using IVector1 = Vector<1, Int32>;
   using UIVector1 = Vector<1, UInt32>;
   using BVector1 = Vector<1, bool>;
   using DVector1 = Vector<1, double>;


   // Nom member operators
   template <typename T>
   inline constexpr Vector<1, T> operator+(const Vector<1, T>& va,
      const Vector<1, T>& vb);

   template <typename T>
   inline constexpr Vector<1, T> operator-(const Vector<1, T>& v);

   template <typename T>
   inline constexpr Vector<1, T> operator-(const Vector<1, T>& va,
      const Vector<1, T>& vb);

   template <typename T>
   inline constexpr Vector<1, T> operator*(const Vector<1, T>& va,
      const Vector<1, T>& vb);

   template <typename T>
   inline constexpr Vector<1, T> operator*(const T& scalar,
      const Vector<1, T>& v);

   template <typename T>
   inline constexpr Vector<1, T> operator*(const Vector<1, T>& v,
      const T& scalar);

   template <typename T>
   inline constexpr Vector<1, T> operator/(const Vector<1, T>& v,
      const T& scalar);

   
   // Relational operators
   template <typename T>
   inline constexpr bool operator==(const Vector<1, T>& va,
      const Vector<1, T>& vb);

   template <typename T>
   inline constexpr bool operator!=(const Vector<1, T>& va,
      const Vector<1, T>& vb);


   // Vector operations
   template <typename T>
   inline T dot(const Vector<1, T>& va, const Vector<1, T>& vb);

   template <typename T>
   inline T norm(const Vector<1, T>& v);

   template <typename T>
   inline Vector<1, T> normalize(const Vector<1, T>& v);
}

#include "Neat/Math/Types/Vector1.inl"
