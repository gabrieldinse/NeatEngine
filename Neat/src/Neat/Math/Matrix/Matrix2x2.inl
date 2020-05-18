#pragma once


namespace Neat
{
   // Default constructor
   template <typename T>
   inline constexpr
   Matrix<2, 2, T>::Matrix() : m_flattened{} {}


   // Basic constructors
   template <typename T>
   inline constexpr
   Matrix<2, 2, T>::Matrix(
      T m00, T m01,
      T m10, T m11)
      : m_flattened{
         m00, m01,
         m10, m11
      }
   {}

   template <typename T>
   inline constexpr
   Matrix<2, 2, T>::Matrix(T scalar)
      : m_flattened{
         scalar, static_cast<T>(0),
         static_cast<T>(0), scalar
         } {}

   template <typename T>
   inline constexpr
   Matrix<2, 2, T>::Matrix(const Matrix<2, 2, T>& m)
      : m_flattened{
         m[0][0], m[0][1],
         m[1][0], m[1][1]
         } {}


   // Conversion constructors
   template <typename T>
   template <
      typename X1, typename Y1,
      typename X2, typename Y2>
   inline constexpr
   Matrix<2, 2, T>::Matrix(
      X1 m00, Y1 m01,
      X2 m10, Y2 m11)
      : m_flattened{
         static_cast<T(m00), static_cast<T(m01),
         static_cast<T(m10), static_cast<T(m11)
      }
   {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<2, 2, T>::Matrix(const Matrix<2, 2, U>& m)
      : m_flattened{
         static_cast<T>(m[0][0]), static_cast<T>(m[0][1]),
         static_cast<T>(m[1][0]), static_cast<T>(m[1][1]),
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<2, 2, T>::Matrix(const Matrix<4, 4, U>& m)
      : m_flattened{
         static_cast<T>(m[0][0]), static_cast<T>(m[0][1]),
         static_cast<T>(m[1][0]), static_cast<T>(m[1][1]),
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<2, 2, T>::Matrix(const Matrix<3, 3, U>& m)
      : m_flattened{
         static_cast<T>(m[0][0]), static_cast<T>(m[0][1]),
         static_cast<T>(m[1][0]), static_cast<T>(m[1][1])
         } {}

   // Non member operators
   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator+(const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb)
   {
      return Matrix<2, 2, T>(
         ma[0][0] + mb[0][0], ma[0][1] + mb[0][1],
         ma[1][0] + mb[1][0], ma[1][1] + mb[1][1]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator-(const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb)
   {
      return Matrix<2, 2, T>(
         ma[0][0] - mb[0][0], ma[0][1] - mb[0][1],
         ma[1][0] - mb[1][0], ma[1][1] - mb[1][1]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator*(const Matrix<2, 2, T>& ma, const Matrix<2, 2, T>& mb)
   {
      return Matrix<2, 2, T>(
         ma[0][0] * mb[0][0] + ma[0][1] * mb[1][0],
         ma[0][0] * mb[0][1] + ma[0][1] * mb[1][1],
         ma[1][0] * mb[0][0] + ma[1][1] * mb[1][0],
         ma[1][0] * mb[0][1] + ma[1][1] * mb[1][1],
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator*(T scalar, const Matrix<2, 2, T>& m)
   {
      return Matrix<2, 2, T>(
         m[0][0] * scalar + m[0][1] * scalar,
         m[1][0] * scalar + m[1][1] * scalar
         );
   }

   template <typename T>
   inline constexpr
   Matrix<2, 2, T> operator*(const Matrix<2, 2, T>& m, T scalar)
   {
      return scalar * m;
   }

   template <typename T>
   inline constexpr
   Vector<2, T> operator*(const Matrix<2, 2, T>& m, const Vector<2, T>& v)
   {
      return Vector<2, T>(
         m[0][0] * v[0] + m[0][1] * v[1],
         m[1][0] * v[0] + m[1][1] * v[1]
         );
   }


   // Element accessing
   template <typename T>
   inline constexpr
   typename Matrix<2, 2, T>::RowType& Matrix<2, 2, T>::operator[](std::size_t row)
   {
      return m_rows[row];
   }

   template <typename T>
   inline constexpr
   const typename Matrix<2, 2, T>::RowType& Matrix<2, 2, T>::operator[](
      std::size_t row) const
   {
      return m_rows[row];
   }

   template <typename T>
   inline constexpr
   T& Matrix<2, 2, T>::operator()(std::size_t pos)
   {
      return m_flattened[pos];
   }

   template <typename T>
   inline constexpr
   const T& Matrix<2, 2, T>::operator()(std::size_t pos) const
   {
      return m_flattened[pos];
   }
}