#include "Core/Assert.hpp"

namespace Neat {
// Default constructor
template <typename T>
inline constexpr Matrix<4, 4, T>::Matrix()
    : elements{One<T>,  Zero<T>, Zero<T>, Zero<T>, Zero<T>, One<T>,
               Zero<T>, Zero<T>, Zero<T>, Zero<T>, One<T>,  Zero<T>,
               Zero<T>, Zero<T>, Zero<T>, One<T>} {}

// Basic constructors
template <typename T>
inline constexpr Matrix<4, 4, T>::Matrix(
    const T &m00, const T &m01, const T &m02, const T &m03, const T &m10,
    const T &m11, const T &m12, const T &m13, const T &m20, const T &m21,
    const T &m22, const T &m23, const T &m30, const T &m31, const T &m32,
    const T &m33)
    : elements{m00, m01, m02, m03, m10, m11, m12, m13,
               m20, m21, m22, m23, m30, m31, m32, m33} {}

template <typename T>
inline constexpr Matrix<4, 4, T>::Matrix(const T &scalar)
    : elements{scalar,  Zero<T>, Zero<T>, Zero<T>, Zero<T>, scalar,
               Zero<T>, Zero<T>, Zero<T>, Zero<T>, scalar,  Zero<T>,
               Zero<T>, Zero<T>, Zero<T>, scalar} {}

template <typename T>
inline constexpr Matrix<4, 4, T>::Matrix(const std::array<T, 4 * 4> &data)
    : elements{data} {}

// Copy constructor
template <typename T>
inline constexpr Matrix<4, 4, T>::Matrix(const Matrix<4, 4, T> &m)
    : elements{m.elements} {}

// Conversion constructors
template <typename T>
template <typename X1, typename Y1, typename Z1, typename W1, typename X2,
          typename Y2, typename Z2, typename W2, typename X3, typename Y3,
          typename Z3, typename W3, typename X4, typename Y4, typename Z4,
          typename W4>
inline constexpr Matrix<4, 4, T>::Matrix(
    const X1 &m00, const Y1 &m01, const Z1 &m02, const W1 &m03, const X2 &m10,
    const Y2 &m11, const Z2 &m12, const W2 &m13, const X3 &m20, const Y3 &m21,
    const Z3 &m22, const W3 &m23, const X4 &m30, const Y4 &m31, const Z4 &m32,
    const W4 &m33)
    : elements{static_cast<T>(m00), static_cast<T>(m01), static_cast<T>(m02),
               static_cast<T>(m03), static_cast<T>(m10), static_cast<T>(m11),
               static_cast<T>(m12), static_cast<T>(m13), static_cast<T>(m20),
               static_cast<T>(m21), static_cast<T>(m22), static_cast<T>(m23),
               static_cast<T>(m30), static_cast<T>(m31), static_cast<T>(m32),
               static_cast<T>(m33)} {}

template <typename T>
template <typename U>
inline constexpr Matrix<4, 4, T>::Matrix(const Matrix<4, 4, U> &m)
    : elements{static_cast<T>(m(0, 0)), static_cast<T>(m(0, 1)),
               static_cast<T>(m(0, 2)), static_cast<T>(m(0, 3)),
               static_cast<T>(m(1, 0)), static_cast<T>(m(1, 1)),
               static_cast<T>(m(1, 2)), static_cast<T>(m(1, 3)),
               static_cast<T>(m(2, 0)), static_cast<T>(m(2, 1)),
               static_cast<T>(m(2, 2)), static_cast<T>(m(2, 3)),
               static_cast<T>(m(3, 0)), static_cast<T>(m(3, 1)),
               static_cast<T>(m(3, 2)), static_cast<T>(m(3, 3))} {}

template <typename T>
template <typename U>
inline constexpr Matrix<4, 4, T>::Matrix(const Matrix<3, 3, U> &m)
    : elements{static_cast<T>(m(0, 0)),
               static_cast<T>(m(0, 1)),
               static_cast<T>(m(0, 2)),
               Zero<T>,
               static_cast<T>(m(1, 0)),
               static_cast<T>(m(1, 1)),
               static_cast<T>(m(1, 2)),
               Zero<T>,
               static_cast<T>(m(2, 0)),
               static_cast<T>(m(2, 1)),
               static_cast<T>(m(2, 2)),
               Zero<T>,
               Zero<T>,
               Zero<T>,
               Zero<T>,
               One<T>} {}

template <typename T>
template <typename U>
inline constexpr Matrix<4, 4, T>::Matrix(const Matrix<2, 2, U> &m)
    : elements{static_cast<T>(m(0, 0)),
               static_cast<T>(m(0, 1)),
               Zero<T>,
               Zero<T>,
               static_cast<T>(m(1, 0)),
               static_cast<T>(m(1, 1)),
               Zero<T>,
               Zero<T>,
               Zero<T>,
               Zero<T>,
               One<T>,
               Zero<T>,
               Zero<T>,
               Zero<T>,
               Zero<T>,
               One<T>} {}

template <typename T>
template <typename V1, typename V2, typename V3, typename V4>
inline constexpr Matrix<4, 4, T>::Matrix(const Vector<4, V1> &row1,
                                         const Vector<4, V2> &row2,
                                         const Vector<4, V3> &row3,
                                         const Vector<4, V4> &row4)
    : elements{static_cast<T>(row1.x()), static_cast<T>(row1.y()),
               static_cast<T>(row1.z()), static_cast<T>(row1.w()),
               static_cast<T>(row2.x()), static_cast<T>(row2.y()),
               static_cast<T>(row2.z()), static_cast<T>(row2.w()),
               static_cast<T>(row3.x()), static_cast<T>(row3.y()),
               static_cast<T>(row3.z()), static_cast<T>(row3.w()),
               static_cast<T>(row4.x()), static_cast<T>(row4.y()),
               static_cast<T>(row4.z()), static_cast<T>(row4.w())} {}

template <typename T>
inline constexpr Matrix<4, 4, T>::Matrix(const T *data, UInt32 count) {
  if (count > size()) {
    count = size();
  }

  std::copy(data, data + count, elements.data());
  std::fill(elements.data() + count, elements.data() + size(), Zero<T>);
}

// Non member operators
template <typename T>
inline constexpr Matrix<4, 4, T> operator+(const Matrix<4, 4, T> &ma,
                                           const Matrix<4, 4, T> &mb) {
  return Matrix<4, 4, T>{
      ma(0) + mb(0),   ma(1) + mb(1),   ma(2) + mb(2),   ma(3) + mb(3),
      ma(4) + mb(4),   ma(5) + mb(5),   ma(6) + mb(6),   ma(7) + mb(7),
      ma(8) + mb(8),   ma(9) + mb(9),   ma(10) + mb(10), ma(11) + mb(11),
      ma(12) + mb(12), ma(13) + mb(13), ma(14) + mb(14), ma(15) + mb(15)};
}

template <typename T>
inline constexpr Matrix<4, 4, T> operator-(const Matrix<4, 4, T> &ma,
                                           const Matrix<4, 4, T> &mb) {
  return Matrix<4, 4, T>{
      ma(0) - mb(0),   ma(1) - mb(1),   ma(2) - mb(2),   ma(3) - mb(3),
      ma(4) - mb(4),   ma(5) - mb(5),   ma(6) - mb(6),   ma(7) - mb(7),
      ma(8) - mb(8),   ma(9) - mb(9),   ma(10) - mb(10), ma(11) - mb(11),
      ma(12) - mb(12), ma(13) - mb(13), ma(14) - mb(14), ma(15) - mb(15)};
}

template <typename T>
inline constexpr Matrix<4, 4, T> operator*(const Matrix<4, 4, T> &ma,
                                           const Matrix<4, 4, T> &mb) {
  return Matrix<4, 4, T>{ma(0, 0) * mb(0, 0) + ma(0, 1) * mb(1, 0) +
                             ma(0, 2) * mb(2, 0) + ma(0, 3) * mb(3, 0),
                         ma(0, 0) * mb(0, 1) + ma(0, 1) * mb(1, 1) +
                             ma(0, 2) * mb(2, 1) + ma(0, 3) * mb(3, 1),
                         ma(0, 0) * mb(0, 2) + ma(0, 1) * mb(1, 2) +
                             ma(0, 2) * mb(2, 2) + ma(0, 3) * mb(3, 2),
                         ma(0, 0) * mb(0, 3) + ma(0, 1) * mb(1, 3) +
                             ma(0, 2) * mb(2, 3) + ma(0, 3) * mb(3, 3),
                         ma(1, 0) * mb(0, 0) + ma(1, 1) * mb(1, 0) +
                             ma(1, 2) * mb(2, 0) + ma(1, 3) * mb(3, 0),
                         ma(1, 0) * mb(0, 1) + ma(1, 1) * mb(1, 1) +
                             ma(1, 2) * mb(2, 1) + ma(1, 3) * mb(3, 1),
                         ma(1, 0) * mb(0, 2) + ma(1, 1) * mb(1, 2) +
                             ma(1, 2) * mb(2, 2) + ma(1, 3) * mb(3, 2),
                         ma(1, 0) * mb(0, 3) + ma(1, 1) * mb(1, 3) +
                             ma(1, 2) * mb(2, 3) + ma(1, 3) * mb(3, 3),
                         ma(2, 0) * mb(0, 0) + ma(2, 1) * mb(1, 0) +
                             ma(2, 2) * mb(2, 0) + ma(2, 3) * mb(3, 0),
                         ma(2, 0) * mb(0, 1) + ma(2, 1) * mb(1, 1) +
                             ma(2, 2) * mb(2, 1) + ma(2, 3) * mb(3, 1),
                         ma(2, 0) * mb(0, 2) + ma(2, 1) * mb(1, 2) +
                             ma(2, 2) * mb(2, 2) + ma(2, 3) * mb(3, 2),
                         ma(2, 0) * mb(0, 3) + ma(2, 1) * mb(1, 3) +
                             ma(2, 2) * mb(2, 3) + ma(2, 3) * mb(3, 3),
                         ma(3, 0) * mb(0, 0) + ma(3, 1) * mb(1, 0) +
                             ma(3, 2) * mb(2, 0) + ma(3, 3) * mb(3, 0),
                         ma(3, 0) * mb(0, 1) + ma(3, 1) * mb(1, 1) +
                             ma(3, 2) * mb(2, 1) + ma(3, 3) * mb(3, 1),
                         ma(3, 0) * mb(0, 2) + ma(3, 1) * mb(1, 2) +
                             ma(3, 2) * mb(2, 2) + ma(3, 3) * mb(3, 2),
                         ma(3, 0) * mb(0, 3) + ma(3, 1) * mb(1, 3) +
                             ma(3, 2) * mb(2, 3) + ma(3, 3) * mb(3, 3)};
}

template <typename T>
inline constexpr Matrix<4, 4, T> operator*(const T &scalar,
                                           const Matrix<4, 4, T> &m) {
  return Matrix<4, 4, T>{
      scalar * m(0),  scalar * m(1),  scalar * m(2),  scalar * m(3),
      scalar * m(4),  scalar * m(5),  scalar * m(6),  scalar * m(7),
      scalar * m(8),  scalar * m(9),  scalar * m(10), scalar * m(11),
      scalar * m(12), scalar * m(13), scalar * m(14), scalar * m(15)};
}

template <typename T>
inline constexpr Matrix<4, 4, T> operator*(const Matrix<4, 4, T> &m,
                                           const T &scalar) {
  return scalar * m;
}

template <typename T>
inline constexpr Vector<4, T> operator*(const Matrix<4, 4, T> &m,
                                        const Vector<4, T> &v) {
  return Vector<4, T>{
      m(0, 0) * v[0] + m(0, 1) * v[1] + m(0, 2) * v[2] + m(0, 3) * v[3],
      m(1, 0) * v[0] + m(1, 1) * v[1] + m(1, 2) * v[2] + m(1, 3) * v[3],
      m(2, 0) * v[0] + m(2, 1) * v[1] + m(2, 2) * v[2] + m(2, 3) * v[3],
      m(3, 0) * v[0] + m(3, 1) * v[1] + m(3, 2) * v[2] + m(3, 3) * v[3]};
}

template <typename T>
inline constexpr Matrix<4, 4, T> operator/(const Matrix<4, 4, T> &m,
                                           const T &scalar) {
  return Matrix<4, 4, T>{
      m(0) / scalar,  m(1) / scalar,  m(2) / scalar,  m(3) / scalar,
      m(4) / scalar,  m(5) / scalar,  m(6) / scalar,  m(7) / scalar,
      m(8) / scalar,  m(9) / scalar,  m(10) / scalar, m(11) / scalar,
      m(12) / scalar, m(13) / scalar, m(14) / scalar, m(15) / scalar};
}

// Assignment operators
template <typename T>
template <typename U>
inline constexpr Matrix<4, 4, T> &Matrix<4, 4, T>::operator=(
    const Matrix<4, 4, U> &m) {
  elements = {
      static_cast<T>(m(0)),  static_cast<T>(m(1)),  static_cast<T>(m(2)),
      static_cast<T>(m(3)),  static_cast<T>(m(4)),  static_cast<T>(m(5)),
      static_cast<T>(m(6)),  static_cast<T>(m(7)),  static_cast<T>(m(8)),
      static_cast<T>(m(9)),  static_cast<T>(m(10)), static_cast<T>(m(11)),
      static_cast<T>(m(12)), static_cast<T>(m(13)), static_cast<T>(m(14)),
      static_cast<T>(m(15))};

  return *this;
}

template <typename T>
inline constexpr Matrix<4, 4, T> &Matrix<4, 4, T>::operator=(
    const Matrix<4, 4, T> &m) {
  elements = m.elements;

  return *this;
}

// Compound assigment operators
template <typename T>
template <typename U>
inline constexpr Matrix<4, 4, T> &Matrix<4, 4, T>::operator+=(
    Matrix<4, 4, U> const &m) {
  elements[0] += m(0);
  elements[1] += m(1);
  elements[2] += m(2);
  elements[3] += m(3);
  elements[4] += m(4);
  elements[5] += m(5);
  elements[6] += m(6);
  elements[7] += m(7);
  elements[8] += m(8);
  elements[9] += m(9);
  elements[10] += m(10);
  elements[11] += m(11);
  elements[12] += m(12);
  elements[13] += m(13);
  elements[14] += m(14);
  elements[15] += m(15);

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<4, 4, T> &Matrix<4, 4, T>::operator-=(const U &scalar) {
  elements[0] -= scalar;
  elements[1] -= scalar;
  elements[2] -= scalar;
  elements[3] -= scalar;
  elements[4] -= scalar;
  elements[5] -= scalar;
  elements[6] -= scalar;
  elements[7] -= scalar;
  elements[8] -= scalar;
  elements[9] -= scalar;
  elements[10] -= scalar;
  elements[11] -= scalar;
  elements[12] -= scalar;
  elements[13] -= scalar;
  elements[14] -= scalar;
  elements[15] -= scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<4, 4, T> &Matrix<4, 4, T>::operator-=(
    Matrix<4, 4, U> const &m) {
  elements[0] -= m(0);
  elements[1] -= m(1);
  elements[2] -= m(2);
  elements[3] -= m(3);
  elements[4] -= m(4);
  elements[5] -= m(5);
  elements[6] -= m(6);
  elements[7] -= m(7);
  elements[8] -= m(8);
  elements[9] -= m(9);
  elements[10] -= m(10);
  elements[11] -= m(11);
  elements[12] -= m(12);
  elements[13] -= m(13);
  elements[14] -= m(14);
  elements[15] -= m(15);

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<4, 4, T> &Matrix<4, 4, T>::operator*=(const U &scalar) {
  elements[0] *= scalar;
  elements[1] *= scalar;
  elements[2] *= scalar;
  elements[3] *= scalar;
  elements[4] *= scalar;
  elements[5] *= scalar;
  elements[6] *= scalar;
  elements[7] *= scalar;
  elements[8] *= scalar;
  elements[9] *= scalar;
  elements[10] *= scalar;
  elements[11] *= scalar;
  elements[12] *= scalar;
  elements[13] *= scalar;
  elements[14] *= scalar;
  elements[15] *= scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<4, 4, T> &Matrix<4, 4, T>::operator*=(
    Matrix<4, 4, U> const &m) {
  return (*this = *this * m);
}

template <typename T>
template <typename U>
inline constexpr Matrix<4, 4, T> &Matrix<4, 4, T>::operator/=(const U &scalar) {
  elements[0] /= scalar;
  elements[1] /= scalar;
  elements[2] /= scalar;
  elements[3] /= scalar;
  elements[4] /= scalar;
  elements[5] /= scalar;
  elements[6] /= scalar;
  elements[7] /= scalar;
  elements[8] /= scalar;
  elements[9] /= scalar;
  elements[10] /= scalar;
  elements[11] /= scalar;
  elements[12] /= scalar;
  elements[13] /= scalar;
  elements[14] /= scalar;
  elements[15] /= scalar;

  return *this;
}

// Element accessing
template <typename T>
inline constexpr std::span<T, 4> Matrix<4, 4, T>::operator[](UInt32 row) {
  NT_CORE_ASSERT(row < M);

  return std::span<T, M>{elements.data() + row * M, M};
}

template <typename T>
inline constexpr std::span<T, 4> Matrix<4, 4, T>::operator[](UInt32 row) const {
  NT_CORE_ASSERT(row < M);

  return std::span<T, M>{elements.data() + row * M, M};
}

template <typename T>
inline constexpr T &Matrix<4, 4, T>::operator()(UInt32 pos) {
  NT_CORE_ASSERT(pos < Size);

  return elements[pos];
}

template <typename T>
inline constexpr const T &Matrix<4, 4, T>::operator()(UInt32 pos) const {
  NT_CORE_ASSERT(pos < Size);

  return elements[pos];
}

template <typename T>
inline constexpr T &Matrix<4, 4, T>::operator()(UInt32 row, UInt32 col) {
  NT_CORE_ASSERT(row < M and col < N);

  return elements[row * M + col];
}

template <typename T>
inline constexpr const T &Matrix<4, 4, T>::operator()(UInt32 row,
                                                      UInt32 col) const {
  NT_CORE_ASSERT(row < M and col < N);

  return elements[row * M + col];
}

template <typename T>
inline constexpr T &Matrix<4, 4, T>::operator[](UInt32 row, UInt32 col) {
  return operator()(row, col);
}

template <typename T>
inline constexpr const T &Matrix<4, 4, T>::operator[](UInt32 row,
                                                      UInt32 col) const {
  return operator()(row, col);
}

template <typename T>
inline constexpr Matrix<4, 4, T>::RowType Matrix<4, 4, T>::row(
    UInt32 row) const {
  NT_CORE_ASSERT(row < M);

  return RowType{elements[row * M], elements[row * M + 1],
                 elements[row * M + 2], elements[row * M + 3]};
}

template <typename T>
inline constexpr Matrix<4, 4, T>::RowType Matrix<4, 4, T>::col(
    UInt32 col) const {
  NT_CORE_ASSERT(col < N);

  return RowType{elements[col], elements[col + M], elements[col + 2 * M],
                 elements[col + 3 * M]};
}

// Relational operators
template <typename T>
template <typename U>
inline constexpr bool Matrix<4, 4, T>::operator==(
    const Matrix<4, 4, U> &m) const {
  return elements[0] == m(0) and elements[1] == m(1) and elements[2] == m(2) and
         elements[3] == m(3) and elements[4] == m(4) and elements[5] == m(5) and
         elements[6] == m(6) and elements[7] == m(7) and elements[8] == m(8) and
         elements[9] == m(9) and elements[10] == m(10) and
         elements[11] == m(11) and elements[12] == m(12) and
         elements[13] == m(13) and elements[14] == m(14) and
         elements[15] == m(15);
}

template <typename T>
template <typename U>
inline constexpr bool Matrix<4, 4, T>::operator!=(
    const Matrix<4, 4, U> &m) const {
  return !(*this == m);
}

// Matrix operations
template <typename T>
inline T determinant(const Matrix<4, 4, T> &m) {
  T sub1 = m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2);
  T sub2 = m(2, 3) * m(3, 1) - m(2, 1) * m(3, 3);
  T sub3 = m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1);
  T sub4 = m(2, 3) * m(3, 0) - m(2, 0) * m(3, 3);
  T sub5 = m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0);
  T sub6 = m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1);
  T sub7 = m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0);
  T sub8 = m(2, 2) * m(3, 0) - m(2, 0) * m(3, 2);

  T det1 = m(1, 1) * sub1 + m(1, 2) * sub2 + m(1, 3) * sub3;
  T det2 = m(1, 0) * sub1 + m(1, 2) * sub4 + m(1, 3) * sub5;
  T det3 = m(1, 0) * sub6 + m(1, 1) * sub4 + m(1, 3) * sub7;
  T det4 = m(1, 0) * sub3 + m(1, 1) * sub8 + m(1, 2) * sub7;

  return m(0, 0) * det1 - m(0, 1) * det2 + m(0, 2) * det3 - m(0, 3) * det4;
}

template <typename T>
inline Matrix<4, 4, T> transpose(const Matrix<4, 4, T> &m) {
  return Matrix<4, 4, T>{m(0, 0), m(1, 0), m(2, 0), m(3, 0), m(0, 1), m(1, 1),
                         m(2, 1), m(3, 1), m(0, 2), m(1, 2), m(2, 2), m(3, 2),
                         m(0, 3), m(1, 3), m(2, 3), m(3, 3)};
}

template <typename T>
inline Matrix<4, 4, T> inverse(const Matrix<4, 4, T> &m) {
  T s0 = m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1);
  T s1 = m(0, 0) * m(1, 2) - m(1, 0) * m(0, 2);
  T s2 = m(0, 0) * m(1, 3) - m(1, 0) * m(0, 3);
  T s3 = m(0, 1) * m(1, 2) - m(1, 1) * m(0, 2);
  T s4 = m(0, 1) * m(1, 3) - m(1, 1) * m(0, 3);
  T s5 = m(0, 2) * m(1, 3) - m(1, 2) * m(0, 3);

  T c5 = m(2, 2) * m(3, 3) - m(3, 2) * m(2, 3);
  T c4 = m(2, 1) * m(3, 3) - m(3, 1) * m(2, 3);
  T c3 = m(2, 1) * m(3, 2) - m(3, 1) * m(2, 2);
  T c2 = m(2, 0) * m(3, 3) - m(3, 0) * m(2, 3);
  T c1 = m(2, 0) * m(3, 2) - m(3, 0) * m(2, 2);
  T c0 = m(2, 0) * m(3, 1) - m(3, 0) * m(2, 1);

  T inverse_determinant =
      One<T> / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

  return Matrix<4, 4, T>(
      (m(1, 1) * c5 - m(1, 2) * c4 + m(1, 3) * c3) * inverse_determinant,
      (-m(0, 1) * c5 + m(0, 2) * c4 - m(0, 3) * c3) * inverse_determinant,
      (m(3, 1) * s5 - m(3, 2) * s4 + m(3, 3) * s3) * inverse_determinant,
      (-m(2, 1) * s5 + m(2, 2) * s4 - m(2, 3) * s3) * inverse_determinant,
      (-m(1, 0) * c5 + m(1, 2) * c2 - m(1, 3) * c1) * inverse_determinant,
      (m(0, 0) * c5 - m(0, 2) * c2 + m(0, 3) * c1) * inverse_determinant,
      (-m(3, 0) * s5 + m(3, 2) * s2 - m(3, 3) * s1) * inverse_determinant,
      (m(2, 0) * s5 - m(2, 2) * s2 + m(2, 3) * s1) * inverse_determinant,
      (m(1, 0) * c4 - m(1, 1) * c2 + m(1, 3) * c0) * inverse_determinant,
      (-m(0, 0) * c4 + m(0, 1) * c2 - m(0, 3) * c0) * inverse_determinant,
      (m(3, 0) * s4 - m(3, 1) * s2 + m(3, 3) * s0) * inverse_determinant,
      (-m(2, 0) * s4 + m(2, 1) * s2 - m(2, 3) * s0) * inverse_determinant,
      (-m(1, 0) * c3 + m(1, 1) * c1 - m(1, 2) * c0) * inverse_determinant,
      (m(0, 0) * c3 - m(0, 1) * c1 + m(0, 2) * c0) * inverse_determinant,
      (-m(3, 0) * s3 + m(3, 1) * s1 - m(3, 2) * s0) * inverse_determinant,
      (m(2, 0) * s3 - m(2, 1) * s1 + m(2, 2) * s0) * inverse_determinant);
}
}  // namespace Neat