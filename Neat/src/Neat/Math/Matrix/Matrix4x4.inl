#include "Matrix4x4.h"
#pragma once


namespace Neat
{
   // Default constructor
   template <typename T>
   inline constexpr
   Matrix<4, 4, T>::Matrix() : m_flattened{} {}


   // Basic constructors
   template <typename T>
   inline constexpr
   Matrix<4, 4, T>::Matrix(
      const T& m00, const T& m01, const T& m02, const T& m03,
      const T& m10, const T& m11, const T& m12, const T& m13,
      const T& m20, const T& m21, const T& m22, const T& m23,
      const T& m30, const T& m31, const T& m32, const T& m33)
      : m_rows{
         RowType(m00, m01, m02, m03),
         RowType(m10, m11, m12, m13),
         RowType(m20, m21, m22, m23),
         RowType(m30, m31, m32, m33)
         } {}

   template <typename T>
   inline constexpr
   Matrix<4, 4, T>::Matrix(const T& scalar)
      : m_rows{
         RowType(scalar, 0, 0, 0),
         RowType(0, scalar, 0, 0),
         RowType(0, 0, scalar, 0),
         RowType(0, 0, 0, scalar)
         } {}


   // Copy constructor
   template <typename T>
   inline constexpr
   Matrix<4, 4, T>::Matrix(const Matrix<4, 4, T>& m)
      : m_rows{m[0], m[1], m[2], m[3]} {}


   // Conversion constructors
   template <typename T>
   template <
      typename X1, typename Y1, typename Z1, typename W1,
      typename X2, typename Y2, typename Z2, typename W2,
      typename X3, typename Y3, typename Z3, typename W3,
      typename X4, typename Y4, typename Z4, typename W4>
   inline constexpr
   Matrix<4, 4, T>::Matrix(
      const X1& m00, const Y1& m01, const Z1& m02, const W1& m03,
      const X2& m10, const Y2& m11, const Z2& m12, const W2& m13,
      const X3& m20, const Y3& m21, const Z3& m22, const W3& m23,
      const X4& m30, const Y4& m31, const Z4& m32, const W4& m33)
      : m_rows{
         RowType(m00, m01, m02, m03),
         RowType(m10, m11, m12, m13),
         RowType(m20, m21, m22, m23),
         RowType(m30, m31, m32, m33)
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<4, 4, T>::Matrix(const Matrix<4, 4, U>& m)
      : m_rows{
         RowType(m[0]),
         RowType(m[1]),
         RowType(m[2]),
         RowType(m[3])
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<4, 4, T>::Matrix(const Matrix<3, 3, U>& m)
      : m_rows{
         RowType(m[0], 0),
         RowType(m[1], 0),
         RowType(m[2], 0),
         RowType(0, 0, 0, 1)
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<4, 4, T>::Matrix(const Matrix<2, 2, U>& m)
      : m_rows{
         RowType(m[0], 0, 0),
         RowType(m[1], 0, 0),
         RowType(0, 0, 1, 0),
         RowType(0, 0, 0, 1)
         } {}

   template<typename T>
   template<typename V1, typename V2, typename V3, typename V4>
   inline constexpr
   Matrix<4, 4, T>::Matrix(
      const Vector<4, V1>& row1,
      const Vector<4, V2>& row2,
      const Vector<4, V3>& row3,
      const Vector<4, V4>& row4)
      : m_rows{
         RowType(row1),
         RowType(row2),
         RowType(row3),
         RowType(row4)
         } {}


   // Non member operators
   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator+(
      const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb)
   {
      return Matrix<4, 4, T>(
         ma[0] + mb[0],
         ma[1] + mb[1],
         ma[2] + mb[2],
         ma[3] + mb[3]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator-(
      const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb)
   {
      return Matrix<4, 4, T>(
         ma[0] - mb[0],
         ma[1] - mb[1],
         ma[2] - mb[2],
         ma[3] - mb[3]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator*(
      const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb)
   {
      return Matrix<4, 4, T>(
         ma[0][0] * mb[0][0] + ma[0][1] * mb[1][0] + ma[0][2] * mb[2][0] + ma[0][3] * mb[3][0],
         ma[0][0] * mb[0][1] + ma[0][1] * mb[1][1] + ma[0][2] * mb[2][1] + ma[0][3] * mb[3][1],
         ma[0][0] * mb[0][2] + ma[0][1] * mb[1][2] + ma[0][2] * mb[2][2] + ma[0][3] * mb[3][2],
         ma[0][0] * mb[0][3] + ma[0][1] * mb[1][3] + ma[0][2] * mb[2][3] + ma[0][3] * mb[3][3],
         ma[1][0] * mb[0][0] + ma[1][1] * mb[1][0] + ma[1][2] * mb[2][0] + ma[1][3] * mb[3][0],
         ma[1][0] * mb[0][1] + ma[1][1] * mb[1][1] + ma[1][2] * mb[2][1] + ma[1][3] * mb[3][1],
         ma[1][0] * mb[0][2] + ma[1][1] * mb[1][2] + ma[1][2] * mb[2][2] + ma[1][3] * mb[3][2],
         ma[1][0] * mb[0][3] + ma[1][1] * mb[1][3] + ma[1][2] * mb[2][3] + ma[1][3] * mb[3][3],
         ma[2][0] * mb[0][0] + ma[2][1] * mb[1][0] + ma[2][2] * mb[2][0] + ma[2][3] * mb[3][0],
         ma[2][0] * mb[0][1] + ma[2][1] * mb[1][1] + ma[2][2] * mb[2][1] + ma[2][3] * mb[3][1],
         ma[2][0] * mb[0][2] + ma[2][1] * mb[1][2] + ma[2][2] * mb[2][2] + ma[2][3] * mb[3][2],
         ma[2][0] * mb[0][3] + ma[2][1] * mb[1][3] + ma[2][2] * mb[2][3] + ma[2][3] * mb[3][3],
         ma[3][0] * mb[0][0] + ma[3][1] * mb[1][0] + ma[3][2] * mb[2][0] + ma[3][3] * mb[3][0],
         ma[3][0] * mb[0][1] + ma[3][1] * mb[1][1] + ma[3][2] * mb[2][1] + ma[3][3] * mb[3][1],
         ma[3][0] * mb[0][2] + ma[3][1] * mb[1][2] + ma[3][2] * mb[2][2] + ma[3][3] * mb[3][2],
         ma[3][0] * mb[0][3] + ma[3][1] * mb[1][3] + ma[3][2] * mb[2][3] + ma[3][3] * mb[3][3]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator*(const T& scalar, const Matrix<4, 4, T>& m)
   {
      return Matrix<4, 4, T>(
         scalar * m[0],
         scalar * m[1],
         scalar * m[2],
         scalar * m[3]
         );
   }

   template <typename T>
   inline constexpr
      Matrix<4, 4, T> operator*(const Matrix<4, 4, T>& m, const T& scalar)
   {
      return scalar * m;
   }

   template <typename T>
   inline constexpr
   Vector<4, T> operator*(const Matrix<4, 4, T>& m, const Vector<4, T>& v)
   {
      return Vector<4, T>(
         m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
         m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
         m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
         m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator/(const Matrix<4, 4, T>& m, const T& scalar)
   {
      return Matrix<4, 4, T>(
         m[0] / scalar,
         m[1] / scalar,
         m[2] / scalar,
         m[3] / scalar
         );
   }


   // Assignment operators
   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<4, 4, T>& Matrix<4, 4, T>::operator=(const Matrix<4, 4, U>& m)
   {
      m_rows[0] = m[0];
      m_rows[1] = m[1];
      m_rows[2] = m[2];
      m_rows[3] = m[3];

      return *this
   }


   // Compound assigment operators
   template<typename T>
	template<typename U>
   inline constexpr
   Matrix<4, 4, T>& Matrix<4, 4, T>::operator+=(Matrix<4, 4, U> const& m)
	{
		m_rows[0] += m[0];
		m_rows[1] += m[1];
		m_rows[2] += m[2];
		m_rows[3] += m[3];

		return *this;
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<4, 4, T>& Matrix<4, 4, T>::operator-=(const U& scalar)
	{
		m_rows[0] -= scalar;
		m_rows[1] -= scalar;
		m_rows[2] -= scalar;
		m_rows[3] -= scalar;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<4, 4, T>& Matrix<4, 4, T>::operator-=(Matrix<4, 4, U> const& m)
	{
		m_rows[0] -= m[0];
		m_rows[1] -= m[1];
		m_rows[2] -= m[2];
		m_rows[3] -= m[3];

		return *this;
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<4, 4, T>& Matrix<4, 4, T>::operator*=(const U& scalar)
	{
		m_rows[0] *= scalar;
		m_rows[1] *= scalar;
		m_rows[2] *= scalar;
		m_rows[3] *= scalar;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<4, 4, T>& Matrix<4, 4, T>::operator*=(Matrix<4, 4, U> const& m)
	{
		return (*this = *this * m);
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<4, 4, T>& Matrix<4, 4, T>::operator/=(const U& scalar)
	{
		m_rows[0] /= scalar;
		m_rows[1] /= scalar;
		m_rows[2] /= scalar;
		m_rows[3] /= scalar;

		return *this;
	}


   // Element accessing
   template <typename T>
   inline constexpr
   typename Matrix<4, 4, T>::RowType& Matrix<4, 4, T>::operator[](std::size_t row)
   {
      return m_rows[row];
   }

   template <typename T>
   inline constexpr
   const typename Matrix<4, 4, T>::RowType& Matrix<4, 4, T>::operator[](
      std::size_t row) const
   {
      return m_rows[row];
   }

   template <typename T>
   inline constexpr
   T& Matrix<4, 4, T>::operator()(std::size_t pos)
   {
      return m_flattened[pos];
   }

   template <typename T>
   inline constexpr
   const T& Matrix<4, 4, T>::operator()(std::size_t pos) const
   {
      return m_flattened[pos];
   }
}