#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"
#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Matrix<3, 3, T>
   {
      using RowType = Vector<3, T>;


      // Default constructor
      constexpr
      Matrix();


      // Basic constructors
      constexpr
      Matrix(
         T m00, T m01, T m02,
         T m10, T m11, T m12,
         T m20, T m21, T m22);

      constexpr explicit
      Matrix(T scalar);


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
         X1 m00, Y1 m01, Z1 m02,
         X2 m10, Y2 m11, Z2 m12,
         X3 m20, Y3 m21, Z3 m22);

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
         const Vector<3, V1> row1,
         const Vector<3, V2> row2,
         const Vector<3, V3> row3);


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
      Matrix<3, 3, T> & operator-=(U scalar);

	   template<typename U>
	   constexpr
      Matrix<3, 3, T> & operator-=(Matrix<3, 3, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<3, 3, T> & operator*=(U scalar);

	   template<typename U>
	   constexpr
      Matrix<3, 3, T>& operator*=(Matrix<3, 3, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<3, 3, T>& operator/=(U scalar);


      constexpr std::size_t size() const { return 3 * 3; }

      // Elements acessing
      constexpr T* dataPointer() { return m_flattened; }
      constexpr const T* dataPointer() const { return m_flattened; }

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
   Matrix<3, 3, T> operator*(T scalar, const Matrix<3, 3, T>& m);

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& m, T scalar);

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Matrix<3, 3, T>& m, const Vector<3, T>& v);

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator/(const Matrix<3, 3, T>& m, T scalar);
}

#include "Neat/Math/Matrix/Matrix3x3.inl"