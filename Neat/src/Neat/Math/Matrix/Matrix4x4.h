#pragma once

#include "Neat/Math/Matrix/MatrixMxN.h"
#include "Neat/Math/Vector/VectorN.h"


namespace Neat
{
   template <typename T>
   struct Matrix<4, 4, T>
   {
      using RowType = Vector<4, T>;
      using ElementType = T;


      // Default constructor
      constexpr
      Matrix();


      // Basic constructors
      constexpr
      Matrix(
         const T& m00, const T& m01, const T& m02, const T& m03,
         const T& m10, const T& m11, const T& m12, const T& m13,
         const T& m20, const T& m21, const T& m22, const T& m23,
         const T& m30, const T& m31, const T& m32, const T& m33);

      constexpr explicit
      Matrix(const T& scalar);


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
         const X1& m00, const Y1& m01, const Z1& m02, const W1& m03,
         const X2& m10, const Y2& m11, const Z2& m12, const W2& m13,
         const X3& m20, const Y3& m21, const Z3& m22, const W3& m23,
         const X4& m30, const Y4& m31, const Z4& m32, const W4& m33);

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
         const Vector<4, V1>& row1,
         const Vector<4, V2>& row2,
         const Vector<4, V3>& row3,
         const Vector<4, V4>& row4);

      Matrix(const T* data)
      {
         for (std::size_t i = 0; i < 4 * 4; ++i)
         {
            m_flattened[i] = data[i];
         }
      }


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
      Matrix<4, 4, T> & operator-=(const U& scalar);

	   template<typename U>
	   constexpr
      Matrix<4, 4, T> & operator-=(Matrix<4, 4, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<4, 4, T> & operator*=(const U& scalar);

	   template<typename U>
	   constexpr
      Matrix<4, 4, T>& operator*=(Matrix<4, 4, U> const& m);

	   template<typename U>
	   constexpr
      Matrix<4, 4, T>& operator/=(const U& scalar);


      constexpr std::size_t size() const { return 4 * 4; }

      // Elements acessing
      constexpr T* data() { return m_flattened; }
      constexpr const T* data() const { return m_flattened; }

      constexpr RowType& operator[](std::size_t row);
      constexpr const RowType& operator[](std::size_t row) const;

      constexpr T& operator()(std::size_t pos);
      constexpr const T& operator()(std::size_t pos) const;

      // Static member functions
      static constexpr
      Matrix<4, 4, T> identity() { return Matrix<4, 4, T>(static_cast<T>(1)); }

   private:
      // Class data
      union
      {
         RowType m_rows[4];
         T m_flattened[4 * 4];
      };
   };
   

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator+(
      const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator-(
      const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator*(
      const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb);

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator*(const T& scalar, const Matrix<4, 4, T>& m);

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator*(const Matrix<4, 4, T>& m, const T& scalar);

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(const Matrix<4, 4, T>& m, const Vector<4, T>& v);

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator/(const Matrix<4, 4, T>& m, const T& scalar);
}

#include "Neat/Math/Matrix/Matrix4x4.inl"