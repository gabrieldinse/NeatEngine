#pragma once

namespace Neat {
// Default constructor
template <typename T>
inline constexpr Matrix<3, 3, T>::Matrix()
    : m_rows{RowType(1, 0, 0), RowType(0, 1, 0), RowType(0, 0, 1)} {}

// Basic constructors
template <typename T>
inline constexpr Matrix<3, 3, T>::Matrix(const T &m00, const T &m01,
                                         const T &m02, const T &m10,
                                         const T &m11, const T &m12,
                                         const T &m20, const T &m21,
                                         const T &m22)
    : m_rows{RowType(m00, m01, m02), RowType(m10, m11, m12),
             RowType(m20, m21, m22)} {}

template <typename T>
inline constexpr Matrix<3, 3, T>::Matrix(const T &scalar)
    : m_rows{RowType(scalar, 0, 0), RowType(0, scalar, 0),
             RowType(0, 0, scalar)} {}

// Copy constrcutor
template <typename T>
inline constexpr Matrix<3, 3, T>::Matrix(const Matrix<3, 3, T> &m)
    : m_rows{m[0], m[1], m[2]} {}

// Conversion constructors
template <typename T>
template <typename X1, typename Y1, typename Z1, typename X2, typename Y2,
          typename Z2, typename X3, typename Y3, typename Z3>
inline constexpr Matrix<3, 3, T>::Matrix(const X1 &m00, const Y1 &m01,
                                         const Z1 &m02, const X2 &m10,
                                         const Y2 &m11, const Z2 &m12,
                                         const X3 &m20, const Y3 &m21,
                                         const Z3 &m22)
    : m_rows{RowType(m00, m01, m02), RowType(m10, m11, m12),
             RowType(m20, m21, m22)} {}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T>::Matrix(const Matrix<3, 3, U> &m)
    : m_rows{RowType(m[0]), RowType(m[1]), RowType(m[2])} {}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T>::Matrix(const Matrix<4, 4, U> &m)
    : m_rows{RowType(m[0]), RowType(m[1]), RowType(m[2])} {}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T>::Matrix(const Matrix<2, 2, U> &m)
    : m_rows{RowType(m[0], 0), RowType(m[1], 0), RowType(0, 0, 1)} {}

template <typename T>
template <typename V1, typename V2, typename V3>
inline constexpr Matrix<3, 3, T>::Matrix(const Vector<3, V1> &row1,
                                         const Vector<3, V2> &row2,
                                         const Vector<3, V3> &row3)
    : m_rows{RowType(row1), RowType(row2), RowType(row3)} {}

template <typename T>
inline constexpr Matrix<3, 3, T>::Matrix(const T *data, UInt32 count) {
  if (count > size())
    throw MatrixDimensionError("Data size is bigger than Matrix size");

  std::copy(data, data + count, m_flattened);
  std::fill(m_flattened + count, m_flattened + size(), zero<T>);
}

// Non member operators
template <typename T>
inline constexpr Matrix<3, 3, T> operator+(const Matrix<3, 3, T> &ma,
                                           const Matrix<3, 3, T> &mb) {
  return Matrix<3, 3, T>(ma[0] + mb[0], ma[1] + mb[1], ma[2] + mb[2]);
}

template <typename T>
inline constexpr Matrix<3, 3, T> operator-(const Matrix<3, 3, T> &ma,
                                           const Matrix<3, 3, T> &mb) {
  return Matrix<3, 3, T>(ma[0] - mb[0], ma[1] - mb[1], ma[2] - mb[2]);
}

template <typename T>
inline constexpr Matrix<3, 3, T> operator*(const Matrix<3, 3, T> &ma,
                                           const Matrix<3, 3, T> &mb) {
  return Matrix<3, 3, T>(
      ma[0][0] * mb[0][0] + ma[0][1] * mb[1][0] + ma[0][2] * mb[2][0],
      ma[0][0] * mb[0][1] + ma[0][1] * mb[1][1] + ma[0][2] * mb[2][1],
      ma[0][0] * mb[0][2] + ma[0][1] * mb[1][2] + ma[0][2] * mb[2][2],
      ma[1][0] * mb[0][0] + ma[1][1] * mb[1][0] + ma[1][2] * mb[2][0],
      ma[1][0] * mb[0][1] + ma[1][1] * mb[1][1] + ma[1][2] * mb[2][1],
      ma[1][0] * mb[0][2] + ma[1][1] * mb[1][2] + ma[1][2] * mb[2][2],
      ma[2][0] * mb[0][0] + ma[2][1] * mb[1][0] + ma[2][2] * mb[2][0],
      ma[2][0] * mb[0][1] + ma[2][1] * mb[1][1] + ma[2][2] * mb[2][1],
      ma[2][0] * mb[0][2] + ma[2][1] * mb[1][2] + ma[2][2] * mb[2][2]);
}

template <typename T>
inline constexpr Matrix<3, 3, T> operator*(const T &scalar,
                                           const Matrix<3, 3, T> &m) {
  return Matrix<3, 3, T>(scalar * m[0], scalar * m[1], scalar * m[2]);
}

template <typename T>
inline constexpr Matrix<3, 3, T> operator*(const Matrix<3, 3, T> &m,
                                           const T &scalar) {
  return scalar * m;
}

template <typename T>
inline constexpr Vector<3, T> operator*(const Matrix<3, 3, T> &m,
                                        const Vector<3, T> &v) {
  return Vector<3, T>(m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2],
                      m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2],
                      m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2]);
}

template <typename T>
inline constexpr Matrix<3, 3, T> operator/(const Matrix<3, 3, T> &m,
                                           const T &scalar) {
  return Matrix<3, 3, T>(m[0] / scalar, m[1] / scalar, m[2] / scalar);
}

// Assignment operators
template <typename T>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator=(
    const Matrix<3, 3, T> &m) {
  m_rows[0] = m[0];
  m_rows[1] = m[1];
  m_rows[2] = m[2];

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator=(
    const Matrix<3, 3, U> &m) {
  m_rows[0] = m[0];
  m_rows[1] = m[1];
  m_rows[2] = m[2];

  return *this;
}

// Compound assigment operators
template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator+=(
    Matrix<3, 3, U> const &m) {
  m_rows[0] += m[0];
  m_rows[1] += m[1];
  m_rows[2] += m[2];

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator-=(const U &scalar) {
  m_rows[0] -= scalar;
  m_rows[1] -= scalar;
  m_rows[2] -= scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator-=(
    Matrix<3, 3, U> const &m) {
  m_rows[0] -= m[0];
  m_rows[1] -= m[1];
  m_rows[2] -= m[2];

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator*=(const U &scalar) {
  m_rows[0] *= scalar;
  m_rows[1] *= scalar;
  m_rows[2] *= scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator*=(
    Matrix<3, 3, U> const &m) {
  return (*this = *this * m);
}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator/=(const U &scalar) {
  m_rows[0] /= scalar;
  m_rows[1] /= scalar;
  m_rows[2] /= scalar;

  return *this;
}

// Output stream operator
template <typename U>
std::ostream &operator<<(std::ostream &os, const Matrix<3, 3, U> &m) {
  os << "Matrix<3, 3, " << typeid(U).name() << ">{\n";
  for (int i = 0; i < 3; ++i) {
    os << "  " << m[i] << "\n";
  }
  os << "}";
  return os;
}

// Element accessing
template <typename T>
inline constexpr typename Matrix<3, 3, T>::RowType &Matrix<3, 3, T>::operator[](
    UInt32 row) {
  return m_rows[row];
}

template <typename T>
inline constexpr const typename Matrix<3, 3, T>::RowType &
Matrix<3, 3, T>::operator[](UInt32 row) const {
  return m_rows[row];
}

template <typename T>
inline constexpr T &Matrix<3, 3, T>::operator()(UInt32 pos) {
  return m_flattened[pos];
}

template <typename T>
inline constexpr const T &Matrix<3, 3, T>::operator()(UInt32 pos) const {
  return m_flattened[pos];
}

// Matrix operations
template <typename T>
inline T determinant(const Matrix<3, 3, T> &m) {
  return +m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
         m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2]) +
         m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
}

template <typename T>
inline Matrix<3, 3, T> transpose(const Matrix<3, 3, T> &m) {
  return Matrix<3, 3, T>(m[0][0], m[1][0], m[2][0], m[0][1], m[1][1], m[2][1],
                         m[0][2], m[1][2], m[2][2]);
}

template <typename T>
inline Matrix<3, 3, T> inverse(const Matrix<3, 3, T> &m) {
  T inverse_determinant = one<T> / determinant(m);

  return Matrix<3, 3, T>(
      (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * inverse_determinant,
      -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * inverse_determinant,
      (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * inverse_determinant,
      -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * inverse_determinant,
      (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * inverse_determinant,
      -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * inverse_determinant,
      (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * inverse_determinant,
      -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * inverse_determinant,
      (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * inverse_determinant);
}
}  // namespace Neat