#pragma once

#include <array>
#include <span>

#include "Neat/Math/Types/TypeMatrixMxN.hpp"
#include "Neat/Math/Types/TypeVectorN.hpp"
#include "Neat/Math/Types/Vector2.hpp"

namespace Neat {
template <typename T>
struct Matrix<2, 2, T> {
  using Type = Matrix<2, 2, T>;
  using RowType = Vector<2, T>;
  using ValueType = T;

  // Default constructor
  constexpr Matrix();

  // Basic constructors
  constexpr Matrix(const T &m00, const T &m01, const T &m10, const T &m11);

  constexpr explicit Matrix(const T &scalar);
  constexpr Matrix(const std::array<T, 2 * 2> &data);

  // Copy constructor
  constexpr Matrix(const Matrix<2, 2, T> &m);

  // Conversion constructors
  template <typename X1, typename Y1, typename X2, typename Y2>
  constexpr Matrix(const X1 &m00, const Y1 &m01, const X2 &m10, const Y2 &m11);

  template <typename U>
  constexpr explicit Matrix(const Matrix<2, 2, U> &m);
  template <typename U>
  constexpr explicit Matrix(const Matrix<4, 4, U> &m);
  template <typename U>
  constexpr explicit Matrix(const Matrix<3, 3, U> &m);

  template <typename V1, typename V2>
  constexpr Matrix(const Vector<2, V1> &row1, const Vector<2, V2> &row2);

  constexpr Matrix(const T *data, UInt32 count);

  // Static factory constructors
  static constexpr Matrix<2, 2, T> identity() { return Matrix<2, 2, T>{}; }

  // Assignment operators
  constexpr Matrix<2, 2, T> &operator=(const Matrix<2, 2, T> &m);
  template <typename U>
  constexpr Matrix<2, 2, T> &operator=(const Matrix<2, 2, U> &m);

  // Compound assigment operators
  template <typename U>
  constexpr Matrix<2, 2, T> &operator+=(Matrix<2, 2, U> const &m);
  template <typename U>
  constexpr Matrix<2, 2, T> &operator-=(const U &scalar);
  template <typename U>
  constexpr Matrix<2, 2, T> &operator-=(Matrix<2, 2, U> const &m);
  template <typename U>
  constexpr Matrix<2, 2, T> &operator*=(const U &scalar);
  template <typename U>
  constexpr Matrix<2, 2, T> &operator*=(Matrix<2, 2, U> const &m);
  template <typename U>
  constexpr Matrix<2, 2, T> &operator/=(const U &scalar);

  // Elements acessing
  constexpr T *data() { return m_data.data(); }
  constexpr const T *data() const { return m_data.data(); }
  constexpr std::span<T, 2> operator[](UInt32 row);
  constexpr std::span<T, 2> operator[](UInt32 row) const;
  constexpr T &operator()(UInt32 pos);
  constexpr const T &operator()(UInt32 pos) const;
  constexpr T &operator()(UInt32 row, UInt32 col);
  constexpr const T &operator()(UInt32 row, UInt32 col) const;

  constexpr UInt32 size() { return m_data.size(); }

 private:
  std::array<T, 2 * 2> m_data;
};

// Predefined types
using Matrix2F = Matrix<2, 2, float>;
using Matrix2I = Matrix<2, 2, Int32>;
using Matrix2U = Matrix<2, 2, UInt32>;
using Matrix2UI = Matrix<2, 2, UInt32>;
using Matrix2D = Matrix<2, 2, double>;
using Matrix2B = Matrix<2, 2, bool>;

// Nom member operators
template <typename T>
inline constexpr Matrix<2, 2, T> operator+(const Matrix<2, 2, T> &ma,
                                           const Matrix<2, 2, T> &mb);

template <typename T>
inline constexpr Matrix<2, 2, T> operator-(const Matrix<2, 2, T> &ma,
                                           const Matrix<2, 2, T> &mb);

template <typename T>
inline constexpr Matrix<2, 2, T> operator*(const Matrix<2, 2, T> &ma,
                                           const Matrix<2, 2, T> &mb);

template <typename T>
inline constexpr Matrix<2, 2, T> operator*(const T &scalar,
                                           const Matrix<2, 2, T> &m);

template <typename T>
inline constexpr Matrix<2, 2, T> operator*(const Matrix<2, 2, T> &m,
                                           const T &scalar);

template <typename T>
inline constexpr Vector<2, T> operator*(const Matrix<2, 2, T> &m,
                                        const Vector<2, T> &v);

template <typename T>
inline constexpr Matrix<2, 2, T> operator/(const Matrix<2, 2, T> &m,
                                           const T &scalar);

// Output stream operator
template <typename U>
std::ostream &operator<<(std::ostream &os, const Matrix<2, 2, U> &m);

// Matrix operations
template <typename T>
inline T determinant(const Matrix<2, 2, T> &m);

template <typename T>
inline Matrix<2, 2, T> transpose(const Matrix<2, 2, T> &m);

template <typename T>
inline Matrix<2, 2, T> inverse(const Matrix<2, 2, T> &m);
}  // namespace Neat

#include "Neat/Math/Types/Matrix2x2.inl"