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
      T m00, T m01, T m02, T m03,
      T m10, T m11, T m12, T m13,
      T m20, T m21, T m22, T m23,
      T m30, T m31, T m32, T m33)
      : m_flattened{
         m00, m01, m02, m03,
         m10, m11, m12, m13,
         m20, m21, m22, m23,
         m30, m31, m32, m33
         } {}

   template <typename T>
   inline constexpr
   Matrix<4, 4, T>::Matrix(T scalar)
      : m_flattened{
         scalar, static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
         static_cast<T>(0), scalar, static_cast<T>(0), static_cast<T>(0),
         static_cast<T>(0), static_cast<T>(0), scalar, static_cast<T>(0),
         static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), scalar
         } {}


   // Copy constructor
   template <typename T>
   inline constexpr
   Matrix<4, 4, T>::Matrix(const Matrix<4, 4, T>& m)
      : m_flattened{
         m[0][0], m[0][1], m[0][2], m[0][3],
         m[1][0], m[1][1], m[1][2], m[1][3],
         m[2][0], m[2][1], m[2][2], m[2][3],
         m[3][0], m[3][1], m[3][2], m[3][3]
         } {}


   // Conversion constructors
   template <typename T>
   template <
      typename X1, typename Y1, typename Z1, typename W1,
      typename X2, typename Y2, typename Z2, typename W2,
      typename X3, typename Y3, typename Z3, typename W3,
      typename X4, typename Y4, typename Z4, typename W4>
   inline constexpr
   Matrix<4, 4, T>::Matrix(
      X1 m00, Y1 m01, Z1 m02, W1 m03,
      X2 m10, Y2 m11, Z2 m12, W2 m13,
      X3 m20, Y3 m21, Z3 m22, W3 m23,
      X4 m30, Y4 m31, Z4 m32, W4 m33)
      : m_flattened{
         static_cast<T>(m00),
         static_cast<T>(m01),
         static_cast<T>(m02),
         static_cast<T>(m03),
         static_cast<T>(m10),
         static_cast<T>(m11),
         static_cast<T>(m12),
         static_cast<T>(m13),
         static_cast<T>(m20),
         static_cast<T>(m21),
         static_cast<T>(m22),
         static_cast<T>(m23),
         static_cast<T>(m30),
         static_cast<T>(m31),
         static_cast<T>(m32),
         static_cast<T>(m33)
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<4, 4, T>::Matrix(const Matrix<4, 4, U>& m)
      : m_flattened{
         static_cast<T>(m[0][0]),
         static_cast<T>(m[0][1]),
         static_cast<T>(m[0][2]),
         static_cast<T>(m[0][3]),
         static_cast<T>(m[1][0]),
         static_cast<T>(m[1][1]),
         static_cast<T>(m[1][2]),
         static_cast<T>(m[1][3]),
         static_cast<T>(m[2][0]),
         static_cast<T>(m[2][1]),
         static_cast<T>(m[2][2]),
         static_cast<T>(m[2][3]),
         static_cast<T>(m[3][0]),
         static_cast<T>(m[3][1]),
         static_cast<T>(m[3][2]),
         static_cast<T>(m[3][3])
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<4, 4, T>::Matrix(const Matrix<3, 3, U>& m)
      : m_flattened{
         static_cast<T>(m[0][0]),
         static_cast<T>(m[0][1]),
         static_cast<T>(m[0][2]),
         static_cast<T>(0),
         static_cast<T>(m[1][0]),
         static_cast<T>(m[1][1]),
         static_cast<T>(m[1][2]),
         static_cast<T>(0),
         static_cast<T>(m[2][0]),
         static_cast<T>(m[2][1]),
         static_cast<T>(m[2][2]),
         static_cast<T>(0),
         static_cast<T>(0),
         static_cast<T>(0),
         static_cast<T>(0),
         static_cast<T>(0)
         } {}

   template <typename T>
   template <typename U>
   inline constexpr
   Matrix<4, 4, T>::Matrix(const Matrix<2, 2, U>& m)
      : m_flattened{
         static_cast<T>(m[0][0]),
         static_cast<T>(m[0][1]),
         static_cast<T>(0),
         static_cast<T>(0),
         static_cast<T>(m[1][0]),
         static_cast<T>(m[1][1]),
         static_cast<T>(0),
         static_cast<T>(0),
         static_cast<T>(0),
         static_cast<T>(0), 
         static_cast<T>(0),
         static_cast<T>(0),
         static_cast<T>(0),
         static_cast<T>(0),
         static_cast<T>(0),
         static_cast<T>(0)
         } {}


   // Non member operators
   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator+(const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb)
   {
      return Matrix<4, 4, T>(
         ma[0][0] + mb[0][0],
         ma[0][1] + mb[0][1],
         ma[0][2] + mb[0][2],
         ma[0][3] + mb[0][3],
         ma[1][0] + mb[1][0],
         ma[1][1] + mb[1][1],
         ma[1][2] + mb[1][2],
         ma[1][3] + mb[1][3],
         ma[2][0] + mb[2][0],
         ma[2][1] + mb[2][1],
         ma[2][2] + mb[2][2],
         ma[2][3] + mb[2][3],
         ma[3][0] + mb[3][0],
         ma[3][1] + mb[3][1],
         ma[3][2] + mb[3][2],
         ma[3][3] + mb[3][3]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator-(const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb)
   {
      return Matrix<4, 4, T>(
         ma[0][0] - mb[0][0],
         ma[0][1] - mb[0][1],
         ma[0][2] - mb[0][2],
         ma[0][3] - mb[0][3],
         ma[1][0] - mb[1][0],
         ma[1][1] - mb[1][1],
         ma[1][2] - mb[1][2],
         ma[1][3] - mb[1][3],
         ma[2][0] - mb[2][0],
         ma[2][1] - mb[2][1],
         ma[2][2] - mb[2][2],
         ma[2][3] - mb[2][3],
         ma[3][0] - mb[3][0],
         ma[3][1] - mb[3][1],
         ma[3][2] - mb[3][2],
         ma[3][3] - mb[3][3]
         );
   }

   template <typename T>
   inline constexpr
   Matrix<4, 4, T> operator*(const Matrix<4, 4, T>& ma, const Matrix<4, 4, T>& mb)
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
   Matrix<4, 4, T> operator*(T scalar, const Matrix<4, 4, T>& m)
   {
      return Matrix<4, 4, T>(
         m[0][0] * scalar + m[0][1] * scalar + m[0][2] * scalar + m[0][3] * scalar,
         m[1][0] * scalar + m[1][1] * scalar + m[1][2] * scalar + m[1][3] * scalar,
         m[2][0] * scalar + m[2][1] * scalar + m[2][2] * scalar + m[2][3] * scalar,
         m[3][0] * scalar + m[3][1] * scalar + m[3][2] * scalar + m[3][3] * scalar
         );
   }

   template <typename T>
   inline constexpr
      Matrix<4, 4, T> operator*(const Matrix<4, 4, T>& m, T scalar)
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