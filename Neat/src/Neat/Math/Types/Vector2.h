#pragma once

#include <type_traits>

#include "Neat/Math/Types/TypeVectorN.h"


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
      constexpr Vector();

      // Basic Constructors
      constexpr explicit Vector(const T& scalar);
      constexpr Vector(const T& x, const T& y);

      // Copy Constructor
      constexpr Vector(const Vector<2, T>& v);

      // Conversion constructors
      template <typename U>
      constexpr explicit Vector(const Vector<2, U>& v);
      template <typename U>
      constexpr explicit Vector(const Vector<4, U>& v);
      template <typename U>
      constexpr explicit Vector(const Vector<3, U>& v);
      template <typename U>
      constexpr explicit Vector(const Vector<1, U>& v);
      template <typename A, typename B>
      constexpr explicit Vector(const Vector<1, A>& v, const B& scalar1);
      template <typename X, typename Y>
      constexpr Vector(const X& x, const Y& y);

      constexpr Vector(const T* data, UInt32 count);

      // Assignment operators
      constexpr Vector<2, T>& operator=(const Vector<2, T>& other) = default;
      template <typename U>
      constexpr Vector<2, T>& operator=(const Vector<2, U>& other);

      // Compound assignment operators
      template <typename U>
      constexpr Vector<2, T>& operator+=(const Vector<2, U>& v);
      template <typename U>
      constexpr Vector<2, T>& operator-=(const Vector<2, U>& v);
      template <typename U>
      constexpr Vector<2, T>& operator*=(const Vector<2, U>& v);
      template <typename U>
      constexpr Vector<2, T>& operator*=(const Vector<1, U>& v);
      template <typename U>
      constexpr Vector<2, T>& operator*=(const U& scalar);
      template <typename U>
      constexpr Vector<2, T>& operator/=(const U& scalar);

      // Explicit conversion operators
      inline constexpr explicit operator bool() const;

      // Element acessing
      constexpr T& operator[](UInt32 pos);
      constexpr const T& operator[](UInt32 pos) const;
      constexpr T& operator()(UInt32 pos) { return (*this)[pos]; }
      constexpr const T& operator()(UInt32 pos) const { return (*this)[pos]; }
      constexpr T* dataPointer() { return &x; }
      constexpr const T* dataPointer() const { return &x; }

      // Static member variables
      static constexpr UInt32 size() { return 2; }
      static constexpr UInt32 length() { return size(); }
   };


   // Predefined types
   using Vector2F = Vector<2, float>;
   using Vector2I = Vector<2, Int32>;
   using Vector2UI = Vector<2, UInt32>;
   using Vector2B = Vector<2, bool>;
   using Vector2D = Vector<2, double>;


   // Nom member operators
   template <typename T>
   inline constexpr Vector<2, T> operator+(const Vector<2, T>& va,
      const Vector<2, T>& vb);

   template <typename T>
   inline constexpr Vector<2, T> operator-(const Vector<2, T>& v);

   template <typename T>
   inline constexpr Vector<2, T> operator-(const Vector<2, T>& va,
      const Vector<2, T>& vb);

   template <typename T>
   inline constexpr Vector<2, T> operator*(const Vector<2, T>& va,
      const Vector<2, T>& vb);

   template <typename T>
   inline constexpr Vector<2, T> operator*(const Vector<2, T>& va,
      const Vector<1, T>& vb);

   template <typename T>
   inline constexpr Vector<2, T> operator*(const T& scalar,
      const Vector<2, T>& v);

   template <typename T>
   inline constexpr Vector<2, T> operator*(const Vector<2, T>& v,
      const T& scalar);

   template <typename T>
   inline constexpr Vector<2, T> operator/(const Vector<2, T>& v,
      const T& scalar);


   // Relational operators
   template <typename T>
   inline constexpr bool operator==(const Vector<2, T>& va,
      const Vector<2, T>& vb);

   template <typename T>
   inline constexpr bool operator!=(const Vector<2, T>& va,
      const Vector<2, T>& vb);


   // Vector operations
   template <typename T>
   inline T dot(const Vector<2, T>& va, const Vector<2, T>& vb);

   template <typename T>
   inline T norm(const Vector<2, T>& v);

   template <typename T>
   inline Vector<2, T> normalize(const Vector<2, T>& v);
}

#include "Neat/Math/Types/Vector2.inl"
