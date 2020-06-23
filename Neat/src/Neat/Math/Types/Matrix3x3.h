#pragma once

#include "Neat/Math/Types/TypeMatrixMxN.h"
#include "Neat/Math/Types/TypeVectorN.h"


namespace Neat
{
   template <typename T>
   struct Matrix<3, 3, T>
   {
      using Type = Matrix<3, 3, T>;
      using RowType = Vector<3, T>;
      using ValueType = T;


      // Default constructor
      constexpr Matrix();

      // Basic constructors
      constexpr Matrix(
         const T& m00, const T& m01, const T& m02,
         const T& m10, const T& m11, const T& m12,
         const T& m20, const T& m21, const T& m22);

      constexpr explicit Matrix(const T& scalar);

      // Copy constrcutor
      constexpr Matrix(const Matrix<3, 3, T>& m);

      // Conversion constructors
      template <
         typename X1, typename Y1, typename Z1,
         typename X2, typename Y2, typename Z2,
         typename X3, typename Y3, typename Z3>
      constexpr Matrix(
         const X1& m00, const Y1& m01, const Z1& m02,
         const X2& m10, const Y2& m11, const Z2& m12,
         const X3& m20, const Y3& m21, const Z3& m22);

      template <typename U>
      constexpr explicit Matrix(const Matrix<3, 3, U>& m);
      template <typename U>
      constexpr explicit Matrix(const Matrix<4, 4, U>& m);
      template <typename U>
      constexpr explicit Matrix(const Matrix<2, 2, U>& m);

      template <typename V1, typename V2, typename V3>
      constexpr Matrix(
         const Vector<3, V1>& row1,
         const Vector<3, V2>& row2,
         const Vector<3, V3>& row3);

      constexpr Matrix(const T* data, UInt32 count);

      // Static factory constructors
      static constexpr Matrix<3, 3, T> identity() { return Matrix<3, 3, T>(); }

      // Assignment operators
      template <typename U>
      constexpr Matrix<3, 3, T>& operator=(const Matrix<3, 3, U>& m);

      // Compound assigment operators
	   template <typename U>
      constexpr Matrix<3, 3, T>& operator+=(Matrix<3, 3, U> const& m);
	   template <typename U>
	   constexpr Matrix<3, 3, T>& operator-=(const U& scalar);
	   template <typename U>
	   constexpr Matrix<3, 3, T>& operator-=(Matrix<3, 3, U> const& m);
	   template <typename U>
	   constexpr Matrix<3, 3, T>& operator*=(const U& scalar);
	   template <typename U>
	   constexpr Matrix<3, 3, T>& operator*=(Matrix<3, 3, U> const& m);
	   template <typename U>
	   constexpr Matrix<3, 3, T>& operator/=(const U& scalar);

      // Elements acessing
      constexpr T* dataPointer() { return m_flattened; }
      constexpr const T* dataPointer() const { return m_flattened; }
      constexpr RowType& operator[](UInt32 row);
      constexpr const RowType& operator[](UInt32 row) const;
      constexpr T& operator()(UInt32 pos);
      constexpr const
      T& operator()(UInt32 pos) const;

      // Static member functions
      static constexpr UInt32 size() { return 3 * 3; }
      static constexpr UInt32 length() { return size(); }

   private:
      // Class data
      union
      {
         RowType m_rows[3];
         T m_flattened[3 * 3];
      };
   };


   // Predefined types
   using Matrix3F = Matrix<3, 3, float>;
   using Matrix3I = Matrix<3, 3, Int32>;
   using Matrix3UI = Matrix<3, 3, UInt32>;
   using Matrix3D = Matrix<3, 3, double>;
   using Matrix3B = Matrix<3, 3, bool>;


   // Nom member operators
   template <typename T>
   inline constexpr Matrix<3, 3, T> operator+(const Matrix<3, 3, T>& ma,
      const Matrix<3, 3, T>& mb);

   template <typename T>
   inline constexpr Matrix<3, 3, T> operator-(const Matrix<3, 3, T>& ma,
      const Matrix<3, 3, T>& mb);

   template <typename T>
   inline constexpr Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& ma,
      const Matrix<3, 3, T>& mb);

   template <typename T>
   inline constexpr Matrix<3, 3, T> operator*(const T& scalar,
      const Matrix<3, 3, T>& m);

   template <typename T>
   inline constexpr Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& m,
      const T& scalar);

   template <typename T>
   inline constexpr Vector<3, T> operator*(const Matrix<3, 3, T>& m,
      const Vector<3, T>& v);

   template <typename T>
   inline constexpr Matrix<3, 3, T> operator/(const Matrix<3, 3, T>& m,
      const T& scalar);


   // Matrix operations
   template <typename T>
   inline T determinant(const Matrix<3, 3, T>& m);

   template <typename T>
   inline Matrix <3, 3, T> transpose(const Matrix<3, 3, T>& m);

   template <typename T>
   inline Matrix<3, 3, T> inverse(const Matrix<3, 3, T>& m);
}

#include "Neat/Math/Types/Matrix3x3.inl"