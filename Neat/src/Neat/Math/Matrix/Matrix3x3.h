#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"
#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Matrix<3, 3, T>
   {
      using RowType = Vector<3, T>;
      using ElementType = T;


      // Default constructor
      constexpr
      Matrix();


      // Basic constructors
      constexpr
      Matrix(
         const T& m00, const T& m01, const T& m02,
         const T& m10, const T& m11, const T& m12,
         const T& m20, const T& m21, const T& m22);

      constexpr explicit
      Matrix(const T& scalar);


      // Copy constrcutor
      constexpr
      Matrix(const Matrix<3, 3, T>& m);


      // Conversion constructors
      template <
         typename X1, typename Y1, typename Z1,
         typename X2, typename Y2, typename Z2,
         typename X3, typename Y3, typename Z3>
      constexpr
      Matrix(
         const X1& m00, const Y1& m01, const Z1& m02,
         const X2& m10, const Y2& m11, const Z2& m12,
         const X3& m20, const Y3& m21, const Z3& m22);

      template <typename U>
      constexpr explicit
      Matrix(const Matrix<3, 3, U>& m);

      template <typename U>
      constexpr explicit
      Matrix(const Matrix<4, 4, U>& m);

      template <typename U>
      constexpr explicit
      Matrix(const Matrix<2, 2, U>& m);

      template <typename V1, typename V2, typename V3>
      constexpr
      Matrix(
         const Vector<3, V1>& row1,
         const Vector<3, V2>& row2,
         const Vector<3, V3>& row3);


      // Assignment operators
      template <typename U>
      constexpr
      Matrix<3, 3, T>& operator=(const Matrix<3, 3, U>& m);


      // Compound assigment operators
	   template<typename U>
      constexpr
      Matrix<3, 3, T>& operator+=(Matrix<3, 3, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<3, 3, T> & operator-=(const U& scalar);

	   template<typename U>
	   constexpr
      Matrix<3, 3, T> & operator-=(Matrix<3, 3, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<3, 3, T> & operator*=(const U& scalar);

	   template<typename U>
	   constexpr
      Matrix<3, 3, T>& operator*=(Matrix<3, 3, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<3, 3, T>& operator/=(const U& scalar);


      constexpr std::size_t size() const { return 3 * 3; }

      // Elements acessing
      constexpr T* data() { return m_flattened; }
      constexpr const T* data() const { return m_flattened; }

      constexpr RowType& operator[](std::size_t row);
      constexpr const RowType& operator[](std::size_t row) const;

      constexpr T& operator()(std::size_t pos);
      constexpr const T& operator()(std::size_t pos) const;

      // Static member functions
      static constexpr
      Matrix<3, 3, T> identity() { return Matrix<3, 3, T>(static_cast<T>(1)); }

   private:
      // Class data
      union
      {
         RowType m_rows[3];
         T m_flattened[3 * 3];
      };
   };


   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator+(
      const Matrix<3, 3, T>& ma, const Matrix<3, 3, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator-(
      const Matrix<3, 3, T>& ma, const Matrix<3, 3, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(
      const Matrix<3, 3, T>& ma, const Matrix<3, 3, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(const T& scalar, const Matrix<3, 3, T>& m);

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& m, const T& scalar);

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Matrix<3, 3, T>& m, const Vector<3, T>& v);

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator/(const Matrix<3, 3, T>& m, const T& scalar);
}

#include "Neat/Math/Matrix/Matrix3x3.inl"