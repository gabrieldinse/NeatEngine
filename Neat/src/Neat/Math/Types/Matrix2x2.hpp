#pragma once

#include "Neat/Math/Types/TypeMatrixMxN.hpp"
#include "Neat/Math/Types/TypeVectorN.hpp"

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
  static constexpr Matrix<2, 2, T> identity() { return Matrix<2, 2, T>(); }

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
  constexpr T *dataPointer() { return m_flattened; }
  constexpr const T *dataPointer() const { return m_flattened; }
  constexpr RowType &operator[](UInt32 row);
  constexpr const RowType &operator[](UInt32 row) const;
  constexpr T &operator()(UInt32 pos);
  constexpr const T &operator()(UInt32 pos) const;

  // Static member functions
  static constexpr UInt32 size() { return 2 * 2; }
  static constexpr UInt32 length() { return size(); }

 private:
  // Class data
  union {
    RowType m_rows[2];
    T m_flattened[2 * 2];
  };
};

// Predefined types
using Matrix2F = Matrix<2, 2, float>;
using Matrix2I = Matrix<2, 2, Int32>;
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

// Matrix operations
template <typename T>
inline T determinant(const Matrix<2, 2, T> &m);

template <typename T>
inline Matrix<2, 2, T> transpose(const Matrix<2, 2, T> &m);

template <typename T>
inline Matrix<2, 2, T> inverse(const Matrix<2, 2, T> &m);
}  // namespace Neat

#include "Neat/Math/Types/Matrix2x2.inl"