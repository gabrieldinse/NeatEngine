#pragma once

namespace Neat {
// Default constructor
template <typename T>
inline constexpr Matrix<2, 2, T>::Matrix()
    : m_data{one<T>, zero<T>, zero<T>, one<T>} {}

// Basic constructors
template <typename T>
inline constexpr Matrix<2, 2, T>::Matrix(const T &m00, const T &m01,
                                         const T &m10, const T &m11)
    : m_data{m00, m01, m10, m11} {}

template <typename T>
inline constexpr Matrix<2, 2, T>::Matrix(const T &scalar)
    : m_data{scalar, zero<T>, zero<T>, scalar} {}

template <typename T>
inline constexpr Matrix<2, 2, T>::Matrix(const std::array<T, 2 * 2> &data)
    : m_data{data} {}

// Copy constructor
template <typename T>
inline constexpr Matrix<2, 2, T>::Matrix(const Matrix<2, 2, T> &m)
    : m_data(m.m_data) {}

// Conversion constructors
template <typename T>
template <typename X1, typename Y1, typename X2, typename Y2>
inline constexpr Matrix<2, 2, T>::Matrix(const X1 &m00, const Y1 &m01,
                                         const X2 &m10, const Y2 &m11)
    : m_data{m00, m01, m10, m11} {}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T>::Matrix(const Matrix<2, 2, U> &m) {
  m_data[0] = static_cast<T>(m(0));
  m_data[1] = static_cast<T>(m(1));
  m_data[2] = static_cast<T>(m(2));
  m_data[3] = static_cast<T>(m(3));
}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T>::Matrix(const Matrix<4, 4, U> &m)
    : m_data{m(0, 0), m(0, 1), m(1, 0), m(1, 1)} {}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T>::Matrix(const Matrix<3, 3, U> &m)
    : m_data{m(0, 0), m(0, 1), m(1, 0), m(1, 1)} {}

template <typename T>
template <typename V1, typename V2>
inline constexpr Matrix<2, 2, T>::Matrix(const Vector<2, V1> &row1,
                                         const Vector<2, V2> &row2)
    : m_data{row1.x(), row1.y(), row2.x(), row2.y()} {}

template <typename T>
inline constexpr Matrix<2, 2, T>::Matrix(const T *data, UInt32 count) {
  if (count > size()) {
    count = size();
  }

  std::copy(data, data + count, m_data.data());
  std::fill(m_data.data() + count, m_data.data() + size(), zero<T>);
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

// Output stream operator
template <typename U>
std::ostream &operator<<(std::ostream &os, const Matrix<2, 2, U> &m) {
  os << "Matrix2<" << typeid(U).name() << ">{";
  for (int i = 0; i < 2; ++i) {
    os << " ";
    for (int j = 0; j < 2; ++j) {
      os << " " << m(i, j);
    }
    os << "\n";
  }
  os << "}";
  return os;
}

// Assignment operators
template <typename T>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator=(
    const Matrix<2, 2, T> &m) {
  m_data = m.m_data;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator=(
    const Matrix<2, 2, U> &m) {
  m_data = m.m_data;

  return *this;
}

// Compound assigment operators
template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator+=(
    Matrix<2, 2, U> const &m) {
  m_data[0] += m(0);
  m_data[1] += m(1);
  m_data[2] += m(2);
  m_data[3] += m(3);

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator-=(const U &scalar) {
  m_data[0] -= scalar;
  m_data[1] -= scalar;
  m_data[2] -= scalar;
  m_data[3] -= scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator-=(
    Matrix<2, 2, U> const &m) {
  m_data[0] -= m(0);
  m_data[1] -= m(1);
  m_data[2] -= m(2);
  m_data[3] -= m(3);

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Matrix<2, 2, T> &Matrix<2, 2, T>::operator*=(const U &scalar) {
  m_data[0] *= scalar;
  m_data[1] *= scalar;
  m_data[2] *= scalar;
  m_data[3] *= scalar;

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
  m_data[0] /= scalar;
  m_data[1] /= scalar;
  m_data[2] /= scalar;
  m_data[3] /= scalar;

  return *this;
}

// Element accessing
template <typename T>
inline constexpr std::span<T, 2> Matrix<2, 2, T>::operator[](UInt32 row) {
  return std::span<T, 2>{m_data.data() + row * 2, 2};
}

template <typename T>
inline constexpr std::span<T, 2> Matrix<2, 2, T>::operator[](UInt32 row) const {
  return std::span<T, 2>{m_data.data() + row * 2, 2};
}

template <typename T>
inline constexpr T &Matrix<2, 2, T>::operator()(UInt32 pos) {
  return m_data[pos];
}

template <typename T>
inline constexpr const T &Matrix<2, 2, T>::operator()(UInt32 pos) const {
  return m_data[pos];
}

template <typename T>
inline constexpr T &Matrix<2, 2, T>::operator()(UInt32 row, UInt32 col) {
  return m_data[row * 2 + col];
}

template <typename T>
inline constexpr const T &Matrix<2, 2, T>::operator()(UInt32 row,
                                                      UInt32 col) const {
  return m_data[row * 2 + col];
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
  T inverse_determinant = one<T> / (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1));

  return Matrix<2, 2, T>(
      m(1, 1) * inverse_determinant, -m(0, 1) * inverse_determinant,
      -m(1, 0) * inverse_determinant, m(0, 0) * inverse_determinant);
}
}  // namespace Neat