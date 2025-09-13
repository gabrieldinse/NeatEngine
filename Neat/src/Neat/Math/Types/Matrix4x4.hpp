#pragma once

#include <array>
#include <span>

#include "Neat/Math/Types/TypeMatrixMxN.hpp"
#include "Neat/Math/Types/TypeVectorN.hpp"
#include "Neat/Math/Types/Vector4.hpp"

namespace Neat {
template <typename T>
struct Matrix<4, 4, T> {
  using Type = Matrix<4, 4, T>;
  using RowType = Vector<4, T>;
  using ValueType = T;

  std::array<T, 4 * 4> elements;

  // Default constructor
  constexpr Matrix();

  // Basic constructors
  constexpr Matrix(const T &m00, const T &m01, const T &m02, const T &m03,
                   const T &m10, const T &m11, const T &m12, const T &m13,
                   const T &m20, const T &m21, const T &m22, const T &m23,
                   const T &m30, const T &m31, const T &m32, const T &m33);

  constexpr explicit Matrix(const T &scalar);
  constexpr Matrix(const std::array<T, 4 * 4> &data);

  // Copy constructor
  constexpr Matrix(const Matrix<4, 4, T> &m);

  // Conversion constructors
  template <typename X1, typename Y1, typename Z1, typename W1, typename X2,
            typename Y2, typename Z2, typename W2, typename X3, typename Y3,
            typename Z3, typename W3, typename X4, typename Y4, typename Z4,
            typename W4>
  constexpr Matrix(const X1 &m00, const Y1 &m01, const Z1 &m02, const W1 &m03,
                   const X2 &m10, const Y2 &m11, const Z2 &m12, const W2 &m13,
                   const X3 &m20, const Y3 &m21, const Z3 &m22, const W3 &m23,
                   const X4 &m30, const Y4 &m31, const Z4 &m32, const W4 &m33);

  template <typename U>
  constexpr explicit Matrix(const Matrix<4, 4, U> &m);
  template <typename U>
  constexpr explicit Matrix(const Matrix<3, 3, U> &m);
  template <typename U>
  constexpr explicit Matrix(const Matrix<2, 2, U> &m);

  template <typename V1, typename V2, typename V3, typename V4>
  constexpr Matrix(const Vector<4, V1> &row1, const Vector<4, V2> &row2,
                   const Vector<4, V3> &row3, const Vector<4, V4> &row4);

  constexpr Matrix(const T *data, UInt32 count);

  // Static factory constructors
  static constexpr Matrix<4, 4, T> identity() { return Matrix<4, 4, T>{}; }

  // Assignment operators
  constexpr Matrix<4, 4, T> &operator=(const Matrix<4, 4, T> &m);
  template <typename U>
  constexpr Matrix<4, 4, T> &operator=(const Matrix<4, 4, U> &m);

  // Compound assigment operators
  template <typename U>
  constexpr Matrix<4, 4, T> &operator+=(Matrix<4, 4, U> const &m);
  template <typename U>
  constexpr Matrix<4, 4, T> &operator-=(const U &scalar);
  template <typename U>
  constexpr Matrix<4, 4, T> &operator-=(Matrix<4, 4, U> const &m);
  template <typename U>
  constexpr Matrix<4, 4, T> &operator*=(const U &scalar);
  template <typename U>
  constexpr Matrix<4, 4, T> &operator*=(Matrix<4, 4, U> const &m);
  template <typename U>
  constexpr Matrix<4, 4, T> &operator/=(const U &scalar);

  // Elements acessing
  constexpr T *data() { return elements.data(); }
  constexpr const T *data() const { return elements.data(); }
  constexpr std::span<T, 4> operator[](UInt32 row);
  constexpr std::span<T, 4> operator[](UInt32 row) const;
  constexpr T &operator()(UInt32 pos);
  constexpr const T &operator()(UInt32 pos) const;
  constexpr T &operator()(UInt32 row, UInt32 col);
  constexpr const T &operator()(UInt32 row, UInt32 col) const;
  constexpr RowType row(UInt32 row) const;
  constexpr RowType col(UInt32 col) const;

  constexpr UInt32 size() { return elements.size(); }
};

// Predefined types
using Matrix4F = Matrix<4, 4, float>;
using Matrix4I = Matrix<4, 4, Int32>;
using Matrix4U = Matrix<4, 4, UInt32>;
using Matrix4UI = Matrix<4, 4, UInt32>;
using Matrix4D = Matrix<4, 4, double>;
using Matrix4B = Matrix<4, 4, bool>;

// Nom member operators
template <typename T>
inline constexpr Matrix<4, 4, T> operator+(const Matrix<4, 4, T> &ma,
                                           const Matrix<4, 4, T> &mb);

template <typename T>
inline constexpr Matrix<4, 4, T> operator-(const Matrix<4, 4, T> &ma,
                                           const Matrix<4, 4, T> &mb);

template <typename T>
inline constexpr Matrix<4, 4, T> operator*(const Matrix<4, 4, T> &ma,
                                           const Matrix<4, 4, T> &mb);

template <typename T>
inline constexpr Matrix<4, 4, T> operator*(const T &scalar,
                                           const Matrix<4, 4, T> &m);

template <typename T>
inline constexpr Matrix<4, 4, T> operator*(const Matrix<4, 4, T> &m,
                                           const T &scalar);

template <typename T>
inline constexpr Vector<4, T> operator*(const Matrix<4, 4, T> &m,
                                        const Vector<4, T> &v);

template <typename T>
inline constexpr Matrix<4, 4, T> operator/(const Matrix<4, 4, T> &m,
                                           const T &scalar);

// Matrix operations
template <typename T>
inline T determinant(const Matrix<4, 4, T> &m);

template <typename T>
inline Matrix<4, 4, T> transpose(const Matrix<4, 4, T> &m);

template <typename T>
inline Matrix<4, 4, T> inverse(const Matrix<4, 4, T> &m);
}  // namespace Neat

#include "Neat/Math/Types/Matrix4x4.inl"