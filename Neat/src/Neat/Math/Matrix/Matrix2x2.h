#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"
#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Matrix<2, 2, T>
   {
      using RowType = Vector<2, T>;


      // Default constructor
      constexpr
      Matrix();


      // Basic constructors
      constexpr
      Matrix(
         T m00, T m01,
         T m10, T m11);

      constexpr explicit
      Matrix(T scalar);

      constexpr
      Matrix(const Matrix<2, 2, T>& m);


      // Conversion constructors
      template <
         typename X1, typename Y1,
         typename X2, typename Y2>
      constexpr
      Matrix(
         X1 m00, Y1 m01,
         X2 m10, Y2 m11);

      template <typename U>
      constexpr explicit
      Matrix(const Matrix<2, 2, U>& m);

      template <typename U>
      constexpr explicit
      Matrix(const Matrix<4, 4, U>& m);

      template <typename U>
      constexpr explicit
      Matrix(const Matrix<3, 3, U>& m);

      template <typename V1, typename V2>
      constexpr
      Matrix(
         const Vector<2, V1> row1,
         const Vector<2, V2> row2);


      // Assignment operators
      template <typename U>
      constexpr
      Matrix<2, 2, T>& operator=(const Matrix<2, 2, U>& m);


      // Compound assigment operators
	   template<typename U>
      constexpr
      Matrix<2, 2, T>& operator+=(Matrix<2, 2, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<2, 2, T> & operator-=(U scalar);

	   template<typename U>
	   constexpr
      Matrix<2, 2, T> & operator-=(Matrix<2, 2, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<2, 2, T> & operator*=(U scalar);

	   template<typename U>
	   constexpr
      Matrix<2, 2, T>& operator*=(Matrix<2, 2, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<2, 2, T>& operator/=(U scalar);


      constexpr UInt size() const { return 2 * 2; }

      // Elements acessing
      constexpr T* dataPointer() { return m_flattened; }
      constexpr const T* dataPointer() const { return m_flattened; }

      constexpr RowType& operator[](std::size_t row);
      constexpr const RowType& operator[](std::size_t row) const;

      constexpr T& operator()(std::size_t pos);
      constexpr const T& operator()(std::size_t pos) const;

   private:
      // Class data
      union
      {
         RowType m_rows[2];
         T m_flattened[2 * 2];
      };
   };


   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator+(
      const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator-(
      const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator*(
      const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator*(T scalar, const Matrix<2, 2, T>& m);

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator*(const Matrix<2, 2, T>& m, T scalar);

   template <typename T>
   inline constexpr
   Vector<2, T> operator*(const Matrix<2, 2, T>& m, const Vector<2, T>& v);

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator/(const Matrix<2, 2, T>& m, T scalar);
}

#include "Neat/Math/Matrix/Matrix2x2.inl"