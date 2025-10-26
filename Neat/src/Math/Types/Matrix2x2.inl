#pragma once

namespace Neat {
// Default constructor
template <typename T>
inline constexpr Matrix<2, 2, T>::Matrix()
    : elements{One<T>, Zero<T>, Zero<T>, One<T>} {}

// Basic constructors
template <typename T>
inline constexpr Matrix<2, 2, T>::Matrix(const T &m00, const T &m01,
                                         const T &m10, const T &m11)
    : elements{m00, m01, m10, m11} {}

template <typename T>
inline constexpr Matrix<2, 2, T>::Matrix(const T &scalar)
    : elements{scalar, Zero<T>, Zero<T>, scalar} {}

template <typename T>
inline constexpr Matrix<2, 2, T>::Matrix(const std::array<T, 2 * 2> &data)
    : elements{data} {}

// Copy constructor
template <typename T>
inline constexpr Matrix<2, 2, T>::Matrix(const Matrix<2, 2, T> &m)
    : elements(m.elements) {}

// Conversion constructors
template <typename T>
template <typename X1, typename Y1, typename X2, typename Y2>
inline constexpr Matrix<2, 2, T>::Matrix(const X1 &m00, const Y1 &m01,
                                         const X2 &m10, const Y2 &m11)
    : elements{static_cast<T>(m00), static_cast<T>(m01), static_cast<T>(m10),
               static_cast<T>(m11)} {}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T>::Matrix(const Matrix<2, 2, U> &m) {
  elements[0] = static_cast<T>(m(0));
  elements[1] = static_cast<T>(m(1));
  elements[2] = static_cast<T>(m(2));
  elements[3] = static_cast<T>(m(3));
}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T>::Matrix(const Matrix<4, 4, U> &m)
    : elements{m(0, 0), m(0, 1), m(1, 0), m(1, 1)} {}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T>::Matrix(const Matrix<3, 3, U> &m)
    : elements{m(0, 0), m(0, 1), m(1, 0), m(1, 1)} {}

template <typename T>
template <typename V1, typename V2>
inline constexpr Matrix<2, 2, T>::Matrix(const Vector<2, V1> &row1,
                                         const Vector<2, V2> &row2)
    : elements{row1.x(), row1.y(), row2.x(), row2.y()} {}

template <typename T>
inline constexpr Matrix<2, 2, T>::Matrix(const T *data, UInt32 count) {
  if (count > size()) {
    count = size();
  }

  std::copy(data, data + count, elements.data());
  std::fill(elements.data() + count, elements.data() + size(), Zero<T>);
}

// Non member operators
template <typename T>
inline constexpr Matrix<2, 2, T> operator+(const Matrix<2, 2, T> &ma,
                                           const Matrix<2, 2, T> &mb) {
  return Matrix<2, 2, T>{ma(0) + mb(0), ma(1) + mb(1), ma(2) + mb(2),
                         ma(3) + mb(3)};
}

template <typename T>
inline constexpr Matrix<2, 2, T> operator-(const Matrix<2, 2, T> &ma,
                                           const Matrix<2, 2, T> &mb) {
  return Matrix<2, 2, T>{ma(0) - mb(0), ma(1) - mb(1), ma(2) - mb(2),
                         ma(3) - mb(3)};
}

template <typename T>
inline constexpr Matrix<2, 2, T> operator*(const Matrix<2, 2, T> &ma,
                                           const Matrix<2, 2, T> &mb) {
  return Matrix<2, 2, T>(ma(0, 0) * mb(0, 0) + ma(0, 1) * mb(1, 0),
                         ma(0, 0) * mb(0, 1) + ma(0, 1) * mb(1, 1),
                         ma(1, 0) * mb(0, 0) + ma(1, 1) * mb(1, 0),
                         ma(1, 0) * mb(0, 1) + ma(1, 1) * mb(1, 1));
}

template <typename T>
inline constexpr Matrix<2, 2, T> operator*(const T &scalar,
                                           const Matrix<2, 2, T> &m) {
  return Matrix<2, 2, T>(scalar * m(0), scalar * m(1), scalar * m(2),
                         scalar * m(3));
}

template <typename T>
inline constexpr Matrix<2, 2, T> operator*(const Matrix<2, 2, T> &m,
                                           const T &scalar) {
  return scalar * m;
}

template <typename T>
inline constexpr Vector<2, T> operator*(const Matrix<2, 2, T> &m,
                                        const Vector<2, T> &v) {
  return Vector<2, T>{m(0, 0) * v[0] + m(0, 1) * v[1],
                      m(1, 0) * v[0] + m(1, 1) * v[1]};
}

template <typename T>
inline constexpr Matrix<2, 2, T> operator/(const Matrix<2, 2, T> &m,
                                           const T &scalar) {
  return Matrix<2, 2, T>{m(0) / scalar, m(1) / scalar, m(2) / scalar,
                         m(3) / scalar};
}

// Assignment operators
template <typename T>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator=(
    const Matrix<2, 2, T> &m) {
  elements = m.elements;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator=(
    const Matrix<2, 2, U> &m) {
  elements = m.elements;

  return *this;
}

// Compound assigment operators
template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator+=(
    Matrix<2, 2, U> const &m) {
  elements[0] += m(0);
  elements[1] += m(1);
  elements[2] += m(2);
  elements[3] += m(3);

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator-=(const U &scalar) {
  elements[0] -= scalar;
  elements[1] -= scalar;
  elements[2] -= scalar;
  elements[3] -= scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator-=(
    Matrix<2, 2, U> const &m) {
  elements[0] -= m(0);
  elements[1] -= m(1);
  elements[2] -= m(2);
  elements[3] -= m(3);

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator*=(const U &scalar) {
  elements[0] *= scalar;
  elements[1] *= scalar;
  elements[2] *= scalar;
  elements[3] *= scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator*=(
    Matrix<2, 2, U> const &m) {
  return (*this = *this * m);
}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator/=(const U &scalar) {
  elements[0] /= scalar;
  elements[1] /= scalar;
  elements[2] /= scalar;
  elements[3] /= scalar;

  return *this;
}

// Element accessing
template <typename T>
inline constexpr std::span<T, 2> Matrix<2, 2, T>::operator[](UInt32 row) {
  NT_CORE_ASSERT(row < M);

  return std::span<T, M>{elements.data() + row * M, M};
}

template <typename T>
inline constexpr std::span<T, 2> Matrix<2, 2, T>::operator[](UInt32 row) const {
  NT_CORE_ASSERT(row < M);

  return std::span<T, M>{elements.data() + row * M, M};
}

template <typename T>
inline constexpr T &Matrix<2, 2, T>::operator()(UInt32 pos) {
  NT_CORE_ASSERT(pos < Size);

  return elements[pos];
}

template <typename T>
inline constexpr const T &Matrix<2, 2, T>::operator()(UInt32 pos) const {
  NT_CORE_ASSERT(pos < Size);

  return elements[pos];
}

template <typename T>
inline constexpr T &Matrix<2, 2, T>::operator()(UInt32 row, UInt32 col) {
  NT_CORE_ASSERT(row < M and col < N);

  return elements[row * M + col];
}

template <typename T>
inline constexpr const T &Matrix<2, 2, T>::operator()(UInt32 row,
                                                      UInt32 col) const {
  NT_CORE_ASSERT(row < M and col < N);

  return elements[row * M + col];
}

template <typename T>
inline constexpr T &Matrix<2, 2, T>::operator[](UInt32 row, UInt32 col) {
  return operator()(row, col);
}

template <typename T>
inline constexpr const T &Matrix<2, 2, T>::operator[](UInt32 row,
                                                      UInt32 col) const {
  return operator()(row, col);
}

template <typename T>
inline constexpr Matrix<2, 2, T>::RowType Matrix<2, 2, T>::row(
    UInt32 row) const {
  NT_CORE_ASSERT(row < M);

  return RowType{elements[row * M], elements[row * M + 1]};
}

template <typename T>
inline constexpr Matrix<2, 2, T>::RowType Matrix<2, 2, T>::col(
    UInt32 col) const {
  NT_CORE_ASSERT(col < N);

  return RowType{elements[col], elements[col + N]};
}

// Relational operators
template <typename T>
template <typename U>
inline constexpr bool Matrix<2, 2, T>::operator==(
    const Matrix<2, 2, U> &m) const {
  return elements[0] == m(0) and elements[1] == m(1) and elements[2] == m(2) and
         elements[3] == m(3);
}

template <typename T>
template <typename U>
inline constexpr bool Matrix<2, 2, T>::operator!=(
    const Matrix<2, 2, U> &m) const {
  return not(*this == m);
}

// Matrix operations
template <typename T>
inline T determinant(const Matrix<2, 2, T> &m) {
  return m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1);
}

template <typename T>
inline Matrix<2, 2, T> transpose(const Matrix<2, 2, T> &m) {
  return Matrix<2, 2, T>(m(0, 0), m(1, 0), m(0, 1), m(1, 1));
}

template <typename T>
inline Matrix<2, 2, T> inverse(const Matrix<2, 2, T> &m) {
  T inverse_determinant = One<T> / (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1));

  return Matrix<2, 2, T>(
      m(1, 1) * inverse_determinant, -m(0, 1) * inverse_determinant,
      -m(1, 0) * inverse_determinant, m(0, 0) * inverse_determinant);
}
}  // namespace Neat