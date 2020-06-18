#pragma once


namespace Neat
{
   // Default constructor
   template <typename T>
   inline constexpr Matrix<2, 2, T>::Matrix() : m_flattened{} {}


   // Basic constructors
   template <typename T>
   inline constexpr Matrix<2, 2, T>::Matrix(
      const T& m00, const T& m01,
      const T& m10, const T& m11)
      : m_rows{
         RowType(m00, m01),
         RowType(m10, m11)
         } {}

   template <typename T>
   inline constexpr Matrix<2, 2, T>::Matrix(const T& scalar)
      : m_rows{
         RowType(scalar, 0),
         RowType(0, scalar)
         } {}

   template <typename T>
   inline constexpr Matrix<2, 2, T>::Matrix(const Matrix<2, 2, T>& m)
      : m_rows{m[0], m[1]} {}


   // Conversion constructors
   template <typename T>
   template <
      typename X1, typename Y1,
      typename X2, typename Y2>
   inline constexpr Matrix<2, 2, T>::Matrix(
      const X1& m00, const Y1& m01,
      const X2& m10, const Y2& m11)
      : m_rows{
         RowType(m00, m01),
         RowType(m10, m11)
         } {}

   template <typename T>
   template <typename U>
   inline constexpr Matrix<2, 2, T>::Matrix(const Matrix<2, 2, U>& m)
      : m_rows{
         RowType(m[0]),
         RowType(m[1])
         } {}

   template <typename T>
   template <typename U>
   inline constexpr Matrix<2, 2, T>::Matrix(const Matrix<4, 4, U>& m)
      : m_rows{
         RowType(m[0]),
         RowType(m[1])
         } {}

   template <typename T>
   template <typename U>
   inline constexpr Matrix<2, 2, T>::Matrix(const Matrix<3, 3, U>& m)
      : m_rows{
         RowType(m[0]),
         RowType(m[1])
         } {}

   template <typename T>
   template <typename V1, typename V2>
   inline constexpr Matrix<2, 2, T>::Matrix(
      const Vector<2, V1>& row1,
      const Vector<2, V2>& row2)
      : m_rows{
         RowType(row1),
         RowType(row2)
         } {}

   template <typename T>
   inline constexpr Matrix<2, 2, T>::Matrix(const T* data, UInt32 count)
   {
      if (count > size())
         throw MatrixDimensionError("Data size is bigger than Matrix size");

      std::copy(data, data + count, m_flattened);
      std::fill(m_flattened + count, m_flattened + size(), zero<T>);
   }


   // Non member operators
   template <typename T>
   inline constexpr Matrix<2, 2, T> operator+(
      const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb)
   {
      return Matrix<2, 2, T>(
         ma[0] + mb[0],
         ma[1] + mb[1]
         );
   }

   template <typename T>
   inline constexpr Matrix<2, 2, T> operator-(
      const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb)
   {
      return Matrix<2, 2, T>(
         ma[0] - mb[0],
         ma[1] - mb[1]
         );
   }

   template <typename T>
   inline constexpr Matrix<2, 2, T> operator*(
      const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb)
   {
      return Matrix<2, 2, T>(
         ma[0][0] * mb[0][0] + ma[0][1] * mb[1][0],
         ma[0][0] * mb[0][1] + ma[0][1] * mb[1][1],
         ma[1][0] * mb[0][0] + ma[1][1] * mb[1][0],
         ma[1][0] * mb[0][1] + ma[1][1] * mb[1][1],
         );
   }

   template <typename T>
   inline constexpr Matrix<2, 2, T> operator*(const T& scalar,
      const Matrix<2, 2, T>& m)
   {
      return Matrix<2, 2, T>(
         scalar * m[0],
         scalar * m[1]
         );
   }

   template <typename T>
   inline constexpr Matrix<2, 2, T> operator*(const Matrix<2, 2, T>& m,
      const T& scalar)
   {
      return scalar * m;
   }

   template <typename T>
   inline constexpr Vector<2, T> operator*(const Matrix<2, 2, T>& m,
      const Vector<2, T>& v)
   {
      return Vector<2, T>(
         m[0][0] * v[0] + m[0][1] * v[1],
         m[1][0] * v[0] + m[1][1] * v[1]
         );
   }

   template <typename T>
   inline constexpr Matrix<2, 2, T> operator/(const Matrix<2, 2, T>& m,
      const T& scalar)
   {
      return Matrix<2, 2, T>(
         m[0] / scalar,
         m[1] / scalar
         );
   }


   // Assignment operators
   template <typename T>
   template <typename U>
   inline constexpr Matrix<2, 2, T>& Matrix<2, 2, T>::operator=(
      const Matrix<2, 2, U>& m)
   {
      m_rows[0] = m[0];
      m_rows[1] = m[1];

      return *this
   }


   // Compound assigment operators
   template <typename T>
	template <typename U>
   inline constexpr Matrix<2, 2, T>& Matrix<2, 2, T>::operator+=(
      Matrix<2, 2, U> const& m)
	{
		m_rows[0] += m[0];
		m_rows[1] += m[1];

		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Matrix<2, 2, T>& Matrix<2, 2, T>::operator-=(
      const U& scalar)
	{
		m_rows[0] -= scalar;
		m_rows[1] -= scalar;

		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Matrix<2, 2, T>& Matrix<2, 2, T>::operator-=(
      Matrix<2, 2, U> const& m)
	{
		m_rows[0] -= m[0];
		m_rows[1] -= m[1];

		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Matrix<2, 2, T>& Matrix<2, 2, T>::operator*=(
      const U& scalar)
	{
		m_rows[0] *= scalar;
		m_rows[1] *= scalar;

		return *this;
	}

	template <typename T>
	template <typename U>
	inline constexpr Matrix<2, 2, T>& Matrix<2, 2, T>::operator*=(
      Matrix<2, 2, U> const& m)
	{
		return (*this = *this * m);
	}

	template <typename T>
	template <typename U>
	inline constexpr Matrix<2, 2, T>& Matrix<2, 2, T>::operator/=(
      const U& scalar)
	{
		m_rows[0] /= scalar;
		m_rows[1] /= scalar;

		return *this;
	}


   // Element accessing
   template <typename T>
   inline constexpr
   typename Matrix<2, 2, T>::RowType& Matrix<2, 2, T>::operator[](UInt32 row)
   {
      return m_rows[row];
   }

   template <typename T>
   inline constexpr
   const typename Matrix<2, 2, T>::RowType& Matrix<2, 2, T>::operator[](
      UInt32 row) const
   {
      return m_rows[row];
   }

   template <typename T>
   inline constexpr T& Matrix<2, 2, T>::operator()(UInt32 pos)
   {
      return m_flattened[pos];
   }

   template <typename T>
   inline constexpr const T& Matrix<2, 2, T>::operator()(UInt32 pos) const
   {
      return m_flattened[pos];
   }


   // Matrix operations
   template <typename T>
   inline T determinant(const Matrix<2, 2, T>& m)
   {
      return m[0][0] * m[1][1] - m[1][0] * m[0][1];
   }

   template <typename T>
   inline Matrix<2, 2, T> transpose(const Matrix<2, 2, T>& m)
   {
      return Matrix<2, 2, T>(
         m[0][0], m[1][0],
         m[0][1], m[1][1]
         );
   }

   template <typename T>
   inline Matrix<2, 2, T> inverse(const Matrix<2, 2, T>& m)
   {
      T one_over_determinant =
         one<T> / (m[0][0] * m[1][1] - m[1][0] * m[0][1]);

      return Matrix<2, 2, T>(
         m[1][1] * one_over_determinant, -m[0][1] * one_over_determinant,
         -m[1][0] * one_over_determinant, m[0][0] * one_over_determinant
         );
   }
}