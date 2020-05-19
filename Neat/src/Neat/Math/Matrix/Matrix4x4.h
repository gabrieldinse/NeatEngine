#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"
#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Matrix<4, 4, T>
   {
      using RowType = Vector<4, T>;


      // Default constructor
      constexpr
      Matrix();


      // Basic constructors
      constexpr
      Matrix(
         T m00, T m01, T m02, T m03,
         T m10, T m11, T m12, T m13,
         T m20, T m21, T m22, T m23,
         T m30, T m31, T m32, T m33);

      constexpr explicit
      Matrix(T scalar);


      // Copy constructor
      constexpr
      Matrix(const Matrix<4, 4, T>& m);


      // Conversion constructors
      template <
         typename X1, typename Y1, typename Z1, typename W1,
         typename X2, typename Y2, typename Z2, typename W2,
         typename X3, typename Y3, typename Z3, typename W3,
         typename X4, typename Y4, typename Z4, typename W4>
      constexpr
      Matrix(
         X1 m00, Y1 m01, Z1 m02, W1 m03,
         X2 m10, Y2 m11, Z2 m12, W2 m13,
         X3 m20, Y3 m21, Z3 m22, W3 m23,
         X4 m30, Y4 m31, Z4 m32, W4 m33);

      template <typename U>
      constexpr explicit
      Matrix(const Matrix<4, 4, U>& m);

      template <typename U>
      constexpr explicit
      Matrix(const Matrix<3, 3, U>& m);

      template <typename U>
      constexpr explicit
      Matrix(const Matrix<2, 2, U>& m);

      template <typename V1, typename V2, typename V3, typename V4>
      constexpr
      Matrix(
         const Vector<4, V1> row1,
         const Vector<4, V2> row2,
         const Vector<4, V3> row3,
         const Vector<4, V4> row4);


      // Assignment operators
      template <typename U>
      constexpr
      Matrix<4, 4, T>& operator=(const Matrix<4, 4, U>& m);


      // Compound assigment operators
	   template<typename U>
      constexpr
      Matrix<4, 4, T>& operator+=(Matrix<4, 4, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<4, 4, T> & operator-=(U scalar);

	   template<typename U>
	   constexpr
      Matrix<4, 4, T> & operator-=(Matrix<4, 4, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<4, 4, T> & operator*=(U scalar);

	   template<typename U>
	   constexpr
      Matrix<4, 4, T>& operator*=(Matrix<4, 4, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<4, 4, T>& operator/=(U scalar);


      constexpr std::size_t size() const { return 4 * 4; }

      // Elements acessing
      constexpr T* dataPointer() { return m_flattened; }
      constexpr const T* dataPointer() const { return m_flattened; }

      constexpr RowType& operator[](std::size_t row);
      constexpr const RowType& operator[](std::size_t row) const;

      constexpr T& operator()(std::size_t pos);
      constexpr const T& operator()(std::size_t pos) const;

      // Class data
      union
      {
         RowType m_rows[4];
         T m_flattened[4 * 4];
      };
   };
   

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator+(const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator-(const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator*(const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator*(T scalar, const Matrix<4, 4, T>& m);

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator*(const Matrix<4, 4, T>& m, T scalar);

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(const Matrix<4, 4, T>& m, const Vector<4, T>& v);
}

#include "Neat/Math/Matrix/Matrix4x4.inl"