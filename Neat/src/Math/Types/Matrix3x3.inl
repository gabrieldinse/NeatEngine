#pragma once

namespace Neat {
// Default constructor
template <typename T>
inline constexpr Matrix<3, 3, T>::Matrix()
    : elements{One<T>,  Zero<T>, Zero<T>, Zero<T>, One<T>,
               Zero<T>, Zero<T>, Zero<T>, One<T>} {}

// Basic constructors
template <typename T>
inline constexpr Matrix<3, 3, T>::Matrix(const T &m00, const T &m01,
                                         const T &m02, const T &m10,
                                         const T &m11, const T &m12,
                                         const T &m20, const T &m21,
                                         const T &m22)
    : elements{m00, m01, m02, m10, m11, m12, m20, m21, m22} {}

template <typename T>
inline constexpr Matrix<3, 3, T>::Matrix(const T &scalar)
    : elements{scalar,  Zero<T>, Zero<T>, Zero<T>, scalar,
               Zero<T>, Zero<T>, Zero<T>, scalar} {}

template <typename T>
inline constexpr Matrix<3, 3, T>::Matrix(const std::array<T, 3 * 3> &data)
    : elements{data} {}

// Copy constrcutor
template <typename T>
inline constexpr Matrix<3, 3, T>::Matrix(const Matrix<3, 3, T> &m)
    : elements{m.elements} {}

// Conversion constructors
template <typename T>
template <typename X1, typename Y1, typename Z1, typename X2, typename Y2,
          typename Z2, typename X3, typename Y3, typename Z3>
inline constexpr Matrix<3, 3, T>::Matrix(const X1 &m00, const Y1 &m01,
                                         const Z1 &m02, const X2 &m10,
                                         const Y2 &m11, const Z2 &m12,
                                         const X3 &m20, const Y3 &m21,
                                         const Z3 &m22)
    : elements{static_cast<T>(m00), static_cast<T>(m01), static_cast<T>(m02),
               static_cast<T>(m10), static_cast<T>(m11), static_cast<T>(m12),
               static_cast<T>(m20), static_cast<T>(m21), static_cast<T>(m22)} {}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T>::Matrix(const Matrix<3, 3, U> &m)
    : elements{m.elements} {}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T>::Matrix(const Matrix<4, 4, U> &m)
    : elements{m(0), m(1), m(2), m(3), m(4), m(5), m(6), m(7), m(8)} {}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T>::Matrix(const Matrix<2, 2, U> &m)
    : elements{m(0),    m(1),    Zero<T>, m(3),    m(4),
               Zero<T>, Zero<T>, Zero<T>, Zero<T>, One<T>} {}

template <typename T>
template <typename V1, typename V2, typename V3>
inline constexpr Matrix<3, 3, T>::Matrix(const Vector<3, V1> &row1,
                                         const Vector<3, V2> &row2,
                                         const Vector<3, V3> &row3)
    : elements{row1.x(), row1.y(), row1.z(), row2.x(), row2.y(),
               row2.z(), row3.x(), row3.y(), row3.z()} {}

template <typename T>
inline constexpr Matrix<3, 3, T>::Matrix(const T *data, UInt32 count) {
  if (count > size()) {
    count = size();
  }

  std::copy(data, data + count, elements.data());
  std::fill(elements.data() + count, elements.data() + size(), Zero<T>);
}

// Non member operators
template <typename T>
inline constexpr Matrix<3, 3, T> operator+(const Matrix<3, 3, T> &ma,
                                           const Matrix<3, 3, T> &mb) {
  return Matrix<3, 3, T>{ma(0) + mb(0), ma(1) + mb(1), ma(2) + mb(2),
                         ma(3) + mb(3), ma(4) + mb(4), ma(5) + mb(5),
                         ma(6) + mb(6), ma(7) + mb(7), ma(8) + mb(8)};
}

template <typename T>
inline constexpr Matrix<3, 3, T> operator-(const Matrix<3, 3, T> &ma,
                                           const Matrix<3, 3, T> &mb) {
  return Matrix<3, 3, T>{ma(0) - mb(0), ma(1) - mb(1), ma(2) - mb(2),
                         ma(3) - mb(3), ma(4) - mb(4), ma(5) - mb(5),
                         ma(6) - mb(6), ma(7) - mb(7), ma(8) - mb(8)};
}

template <typename T>
inline constexpr Matrix<3, 3, T> operator*(const Matrix<3, 3, T> &ma,
                                           const Matrix<3, 3, T> &mb) {
  return Matrix<3, 3, T>{
      ma(0, 0) * mb(0, 0) + ma(0, 1) * mb(1, 0) + ma(0, 2) * mb(2, 0),
      ma(0, 0) * mb(0, 1) + ma(0, 1) * mb(1, 1) + ma(0, 2) * mb(2, 1),
      ma(0, 0) * mb(0, 2) + ma(0, 1) * mb(1, 2) + ma(0, 2) * mb(2, 2),
      ma(1, 0) * mb(0, 0) + ma(1, 1) * mb(1, 0) + ma(1, 2) * mb(2, 0),
      ma(1, 0) * mb(0, 1) + ma(1, 1) * mb(1, 1) + ma(1, 2) * mb(2, 1),
      ma(1, 0) * mb(0, 2) + ma(1, 1) * mb(1, 2) + ma(1, 2) * mb(2, 2),
      ma(2, 0) * mb(0, 0) + ma(2, 1) * mb(1, 0) + ma(2, 2) * mb(2, 0),
      ma(2, 0) * mb(0, 1) + ma(2, 1) * mb(1, 1) + ma(2, 2) * mb(2, 1),
      ma(2, 0) * mb(0, 2) + ma(2, 1) * mb(1, 2) + ma(2, 2) * mb(2, 2)};
}

template <typename T>
inline constexpr Matrix<3, 3, T> operator*(const T &scalar,
                                           const Matrix<3, 3, T> &m) {
  return Matrix<3, 3, T>{scalar * m[0], scalar * m[1], scalar * m[2],
                         scalar * m[3], scalar * m[4], scalar * m[5],
                         scalar * m[6], scalar * m[7], scalar * m[8]};
}

template <typename T>
inline constexpr Matrix<3, 3, T> operator*(const Matrix<3, 3, T> &m,
                                           const T &scalar) {
  return scalar * m;
}

template <typename T>
inline constexpr Vector<3, T> operator*(const Matrix<3, 3, T> &m,
                                        const Vector<3, T> &v) {
  return Vector<3, T>(m(0, 0) * v[0] + m(0, 1) * v[1] + m(0, 2) * v[2],
                      m(1, 0) * v[0] + m(1, 1) * v[1] + m(1, 2) * v[2],
                      m(2, 0) * v[0] + m(2, 1) * v[1] + m(2, 2) * v[2]);
}

template <typename T>
inline constexpr Matrix<3, 3, T> operator/(const Matrix<3, 3, T> &m,
                                           const T &scalar) {
  return Matrix<3, 3, T>{m[0] / scalar, m[1] / scalar, m[2] / scalar,
                         m[3] / scalar, m[4] / scalar, m[5] / scalar,
                         m[6] / scalar, m[7] / scalar, m[8] / scalar};
}

// Assignment operators
template <typename T>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator=(
    const Matrix<3, 3, T> &m) {
  elements = m.elements;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator=(
    const Matrix<3, 3, U> &m) {
  elements = m.elements;

  return *this;
}

// Compound assigment operators
template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator+=(
    Matrix<3, 3, U> const &m) {
  elements[0] += m(0);
  elements[1] += m(1);
  elements[2] += m(2);
  elements[3] += m(3);
  elements[4] += m(4);
  elements[5] += m(5);
  elements[6] += m(6);
  elements[7] += m(7);
  elements[8] += m(8);

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator-=(const U &scalar) {
  elements[0] -= scalar;
  elements[1] -= scalar;
  elements[2] -= scalar;
  elements[3] -= scalar;
  elements[4] -= scalar;
  elements[5] -= scalar;
  elements[6] -= scalar;
  elements[7] -= scalar;
  elements[8] -= scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator-=(
    Matrix<3, 3, U> const &m) {
  elements[0] -= m(0);
  elements[1] -= m(1);
  elements[2] -= m(2);
  elements[3] -= m(3);
  elements[4] -= m(4);
  elements[5] -= m(5);
  elements[6] -= m(6);
  elements[7] -= m(7);
  elements[8] -= m(8);

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<3, 3, T> &Matrix<3, 3, T>::operator*=(const U &scalar) {
  elements[0] *= scalar;
  elements[1] *= scalar;
  elements[2] *= scalar;
  elements[3] *= scalar;
  elements[4] *= scalar;
  elements[5] *= scalar;
  elements[6] *= scalar;
  elements[7] *= scalar;
  elements[8] *= scalar;

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
  elements[0] /= scalar;
  elements[1] /= scalar;
  elements[2] /= scalar;
  elements[3] /= scalar;
  elements[4] /= scalar;
  elements[5] /= scalar;
  elements[6] /= scalar;
  elements[7] /= scalar;
  elements[8] /= scalar;

  return *this;
}

// Element accessing
template <typename T>
inline constexpr std::span<T, 3> Matrix<3, 3, T>::operator[](UInt32 row) {
  NT_CORE_ASSERT(row < M);

  return std::span<T, M>{elements.data() + row * M, M};
}

template <typename T>
inline constexpr std::span<T, 3> Matrix<3, 3, T>::operator[](UInt32 row) const {
  NT_CORE_ASSERT(row < M);

  return std::span<T, M>{elements.data() + row * M, M};
}

template <typename T>
inline constexpr T &Matrix<3, 3, T>::operator()(UInt32 pos) {
  NT_CORE_ASSERT(pos < Size);

  return elements[pos];
}

template <typename T>
inline constexpr const T &Matrix<3, 3, T>::operator()(UInt32 pos) const {
  NT_CORE_ASSERT(pos < Size);

  return elements[pos];
}

template <typename T>
inline constexpr T &Matrix<3, 3, T>::operator()(UInt32 row, UInt32 col) {
  NT_CORE_ASSERT(row < M and col < N);

  return elements[row * M + col];
}

template <typename T>
inline constexpr const T &Matrix<3, 3, T>::operator()(UInt32 row,
                                                      UInt32 col) const {
  NT_CORE_ASSERT(row < M and col < N);

  return elements[row * M + col];
}

template <typename T>
inline constexpr T &Matrix<3, 3, T>::operator[](UInt32 row, UInt32 col) {
  return operator()(row, col);
}

template <typename T>
inline constexpr const T &Matrix<3, 3, T>::operator[](UInt32 row,
                                                      UInt32 col) const {
  return operator()(row, col);
}

template <typename T>
inline constexpr Matrix<3, 3, T>::RowType Matrix<3, 3, T>::row(
    UInt32 row) const {
  NT_CORE_ASSERT(row < M);

  return RowType{elements[row * M], elements[row * M + 1],
                 elements[row * M + 2]};
}

template <typename T>
inline constexpr Matrix<3, 3, T>::RowType Matrix<3, 3, T>::col(
    UInt32 col) const {
  NT_CORE_ASSERT(col < N);

  return RowType{elements[col], elements[col + M], elements[col + 2 * M]};
}

// Relational operators
template <typename T>
template <typename U>
inline constexpr bool Matrix<3, 3, T>::operator==(
    const Matrix<3, 3, U> &m) const {
  return elements[0] == m(0) and elements[1] == m(1) and elements[2] == m(2) and
         elements[3] == m(3) and elements[4] == m(4) and elements[5] == m(5) and
         elements[6] == m(6) and elements[7] == m(7) and elements[8] == m(8);
}

template <typename T>
template <typename U>
inline constexpr bool Matrix<3, 3, T>::operator!=(
    const Matrix<3, 3, U> &m) const {
  return not(*this == m);
}

// Matrix operations
template <typename T>
inline T determinant(const Matrix<3, 3, T> &m) {
  return m(0, 0) * (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) -
         m(1, 0) * (m(0, 1) * m(2, 2) - m(2, 1) * m(0, 2)) +
         m(2, 0) * (m(0, 1) * m(1, 2) - m(1, 1) * m(0, 2));
}

template <typename T>
inline Matrix<3, 3, T> transpose(const Matrix<3, 3, T> &m) {
  return Matrix<3, 3, T>{m(0, 0), m(1, 0), m(2, 0), m(0, 1), m(1, 1),
                         m(2, 1), m(0, 2), m(1, 2), m(2, 2)};
}

template <typename T>
inline Matrix<3, 3, T> inverse(const Matrix<3, 3, T> &m) {
  T inverse_determinant = One<T> / determinant(m);

  return Matrix<3, 3, T>{
      (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) * inverse_determinant,
      -(m(0, 1) * m(2, 2) - m(2, 1) * m(0, 2)) * inverse_determinant,
      (m(0, 1) * m(1, 2) - m(1, 1) * m(0, 2)) * inverse_determinant,
      -(m(1, 0) * m(2, 2) - m(2, 0) * m(1, 2)) * inverse_determinant,
      (m(0, 0) * m(2, 2) - m(2, 0) * m(0, 2)) * inverse_determinant,
      -(m(0, 0) * m(1, 2) - m(1, 0) * m(0, 2)) * inverse_determinant,
      (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)) * inverse_determinant,
      -(m(0, 0) * m(2, 1) - m(2, 0) * m(0, 1)) * inverse_determinant,
      (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1)) * inverse_determinant};
}
}  // namespace Neat