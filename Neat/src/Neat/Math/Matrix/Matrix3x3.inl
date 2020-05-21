#pragma once


namespace Neat
{
   // Default constructor
   template <typename T>
   inline constexpr
   Matrix<3, 3, T>::Matrix() : m_flattened{} {}


   // Basic constructors
   template <typename T>
   inline constexpr
   Matrix<3, 3, T>::Matrix(
      T m00, T m01, T m02,
      T m10, T m11, T m12,
      T m20, T m21, T m22)
      : m_rows{
         RowType(m00, m01, m02),
         RowType(m10, m11, m12),
         RowType(m20, m21, m22)
         } {}

   template <typename T>
   inline constexpr
   Matrix<3, 3, T>::Matrix(T scalar)
      : m_rows{
         RowType(scalar, 0, 0),
         RowType(0, scalar, 0),
         RowType(0, 0, scalar)
         } {}


   // Copy constrcutor
   template <typename T>
   inline constexpr
   Matrix<3, 3, T>::Matrix(const Matrix<3, 3, T>& m)
      : m_rows{m[0], m[1], m[2]} {}


   // Conversion constructors
   template <typename T>
   template <
      typename X1, typename Y1, typename Z1,
      typename X2, typename Y2, typename Z2,
      typename X3, typename Y3, typename Z3>
   inline constexpr
   Matrix<3, 3, T>::Matrix(
      X1 m00, Y1 m01, Z1 m02,
      X2 m10, Y2 m11, Z2 m12,
      X3 m20, Y3 m21, Z3 m22)
      : m_rows{
         RowType(m00, m01, m02),
         RowType(m10, m11, m12),
         RowType(m20, m21, m22)
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<3, 3, T>::Matrix(const Matrix<3, 3, U>& m)
      : m_rows{
         RowType(m[0]),
         RowType(m[1]),
         RowType(m[2])
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<3, 3, T>::Matrix(const Matrix<4, 4, U>& m)
      : m_rows{
         RowType(m[0]),
         RowType(m[1]),
         RowType(m[2])
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<3, 3, T>::Matrix(const Matrix<2, 2, U>& m)
      : m_rows{
         RowType(m[0], 0),
         RowType(m[1], 0),
         RowType(0, 0, 1)
         } {}

   template<typename T>
   template<typename V1, typename V2, typename V3>
   inline constexpr
   Matrix<3, 3, T>::Matrix(
      const Vector<3, V1> row1,
      const Vector<3, V2> row2,
      const Vector<3, V3> row3)
      : m_rows{RowType(row1), RowType(row2), RowType(row3)} {}


   // Non member operators
   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator+(
      const Matrix<3, 3, T>& ma, const Matrix<3, 3, T>& mb)
   {
      return Matrix<3, 3, T>(
         ma[0] + mb[0],
         ma[1] + mb[1],
         ma[2] + mb[2]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator-(
      const Matrix<3, 3, T>& ma, const Matrix<3, 3, T>& mb)
   {
      return Matrix<3, 3, T>(
         ma[0] - mb[0],
         ma[1] - mb[1],
         ma[2] - mb[2]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(
      const Matrix<3, 3, T>& ma, const Matrix<3, 3, T>& mb)
   {
      return Matrix<3, 3, T>(
         ma[0][0] * mb[0][0] + ma[0][1] * mb[1][0] + ma[0][2] * mb[2][0],
         ma[0][0] * mb[0][1] + ma[0][1] * mb[1][1] + ma[0][2] * mb[2][1],
         ma[0][0] * mb[0][2] + ma[0][1] * mb[1][2] + ma[0][2] * mb[2][2],
         ma[1][0] * mb[0][0] + ma[1][1] * mb[1][0] + ma[1][2] * mb[2][0],
         ma[1][0] * mb[0][1] + ma[1][1] * mb[1][1] + ma[1][2] * mb[2][1],
         ma[1][0] * mb[0][2] + ma[1][1] * mb[1][2] + ma[1][2] * mb[2][2],
         ma[2][0] * mb[0][0] + ma[2][1] * mb[1][0] + ma[2][2] * mb[2][0],
         ma[2][0] * mb[0][1] + ma[2][1] * mb[1][1] + ma[2][2] * mb[2][1],
         ma[2][0] * mb[0][2] + ma[2][1] * mb[1][2] + ma[2][2] * mb[2][2]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(T scalar, const Matrix<3, 3, T>& m)
   {
      return Matrix<3, 3, T>(
         scalar * m[0],
         scalar * m[1],
         scalar * m[2]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& m, T scalar)
   {
      return scalar * m;
   }

   template <typename T>
   inline constexpr
   Vector<3, T> operator*(const Matrix<3, 3, T>& m, const Vector<3, T>& v)
   {
      return Vector<3, T>(
         m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2],
         m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2],
         m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<3, 3, T> operator/(const Matrix<3, 3, T>& m, T scalar)
   {
      return Matrix<3, 3, T>(
         m[0] / scalar,
         m[1] / scalar,
         m[2] / scalar
         );
   }


   // Assignment operators
   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<3, 3, T>& Matrix<3, 3, T>::operator=(const Matrix<3, 3, U>& m)
   {
      m_rows[0] = m[0];
      m_rows[1] = m[1];
      m_rows[2] = m[2];

      return *this
   }


   // Compound assigment operators
   template<typename T>
	template<typename U>
   inline constexpr
   Matrix<3, 3, T>& Matrix<3, 3, T>::operator+=(Matrix<3, 3, U> const& m)
	{
		m_rows[0] += m[0];
		m_rows[1] += m[1];
		m_rows[2] += m[2];

		return *this;
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<3, 3, T>& Matrix<3, 3, T>::operator-=(U scalar)
	{
		m_rows[0] -= scalar;
		m_rows[1] -= scalar;
		m_rows[2] -= scalar;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<3, 3, T>& Matrix<3, 3, T>::operator-=(Matrix<3, 3, U> const& m)
	{
		m_rows[0] -= m[0];
		m_rows[1] -= m[1];
		m_rows[2] -= m[2];

		return *this;
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<3, 3, T>& Matrix<3, 3, T>::operator*=(U scalar)
	{
		m_rows[0] *= scalar;
		m_rows[1] *= scalar;
		m_rows[2] *= scalar;

		return *this;
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<3, 3, T>& Matrix<3, 3, T>::operator*=(Matrix<3, 3, U> const& m)
	{
		return (*this = *this * m);
	}

	template<typename T>
	template<typename U>
	inline constexpr
   Matrix<3, 3, T>& Matrix<3, 3, T>::operator/=(U scalar)
	{
		m_rows[0] /= scalar;
		m_rows[1] /= scalar;
		m_rows[2] /= scalar;

		return *this;
	}


   // Element accessing
   template <typename T>
   inline constexpr
   typename Matrix<3, 3, T>::RowType& Matrix<3, 3, T>::operator[](std::size_t row)
   {
      return m_rows[row];
   }

   template <typename T>
   inline constexpr
   const typename Matrix<3, 3, T>::RowType& Matrix<3, 3, T>::operator[](
      std::size_t row) const
   {
      return m_rows[row];
   }

   template <typename T>
   inline constexpr
   T& Matrix<3, 3, T>::operator()(std::size_t pos)
   {
      return m_flattened[pos];
   }

   template <typename T>
   inline constexpr
   const T& Matrix<3, 3, T>::operator()(std::size_t pos) const
   {
      return m_flattened[pos];
   }
}