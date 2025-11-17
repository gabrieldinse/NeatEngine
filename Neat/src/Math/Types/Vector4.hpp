#pragma once

#include <type_traits>
#include <tuple>

#include "TypeVectorN.hpp"

#include "Core/Assert.hpp"

namespace Neat {
template <typename T>
struct Vector<4, T> {
  using Type = Vector<4, T>;
  using ValueType = T;
  static constexpr UInt32 N = 4;

  std::array<T, 4> elements;

  // Default constructor
  constexpr Vector();

  // Basic Constructors
  constexpr explicit Vector(const T &scalar);
  constexpr Vector(const T &x, const T &y, const T &z, const T &w);
  constexpr Vector(const std::array<T, 4> &data);

  // Copy Constructor
  constexpr Vector(const Vector<4, T> &v);

  // Conversion constructors
  template <typename U>
  constexpr explicit Vector(const Vector<4, U> &v);
  template <typename U>
  constexpr explicit Vector(const Vector<3, U> &v);
  template <typename U>
  constexpr explicit Vector(const Vector<2, U> &v);
  template <typename U>
  constexpr explicit Vector(const Vector<1, U> &v);
  template <typename A, typename B>
  constexpr explicit Vector(const Vector<3, A> &v, const B &scalar);

  template <typename A, typename B, typename C>
  constexpr explicit Vector(const Vector<2, A> &v, const B &scalar1,
                            const C &scalar2);

  template <typename A, typename B, typename C, typename D>
  constexpr explicit Vector(const Vector<1, A> &v, const B &scalar1,
                            const C &scalar2, const D &scalar3);

  template <typename X, typename Y, typename Z, typename W>
  constexpr Vector(const X &x, const Y &y, const Z &z, const W &w);

  constexpr Vector(const T *data, UInt32 count);

  // Assignment operators
  constexpr Vector<4, T> &operator=(const Vector<4, T> &other) = default;
  template <typename U>
  constexpr Vector<4, T> &operator=(const Vector<4, U> &other);

  // Compound assignment operators
  template <typename U>
  constexpr Vector<4, T> &operator+=(const Vector<4, U> &v);
  template <typename U>
  constexpr Vector<4, T> &operator-=(const Vector<4, U> &v);
  template <typename U>
  constexpr Vector<4, T> &operator*=(const Vector<4, U> &v);
  template <typename U>
  constexpr Vector<4, T> &operator*=(const U &scalar);
  template <typename U>
  constexpr Vector<4, T> &operator/=(const U &scalar);

  // Explicit conversion operators
  constexpr explicit operator bool() const;

  // Element acessing
  constexpr T &x() { return elements[0]; }
  constexpr const T &x() const { return elements[0]; }
  constexpr T &y() { return elements[1]; }
  constexpr const T &y() const { return elements[1]; }
  constexpr T &z() { return elements[2]; }
  constexpr const T &z() const { return elements[2]; }
  constexpr T &w() { return elements[3]; }
  constexpr const T &w() const { return elements[3]; }

  constexpr T &r() { return x(); }
  constexpr const T &r() const { return x(); }
  constexpr T &g() { return y(); }
  constexpr const T &g() const { return y(); }
  constexpr T &b() { return z(); }
  constexpr const T &b() const { return z(); }
  constexpr T &a() { return w(); }
  constexpr const T &a() const { return w(); }

  constexpr T &i() { return x(); }
  constexpr const T &i() const { return x(); }
  constexpr T &j() { return y(); }
  constexpr const T &j() const { return y(); }
  constexpr T &k() { return z(); }
  constexpr const T &k() const { return z(); }
  constexpr T &l() { return w(); }
  constexpr const T &l() const { return w(); }

  constexpr T &s() { return x(); }
  constexpr const T &s() const { return x(); }
  constexpr T &t() { return y(); }
  constexpr const T &t() const { return y(); }
  constexpr T &p() { return z(); }
  constexpr const T &p() const { return z(); }
  constexpr T &q() { return w(); }
  constexpr const T &q() const { return w(); }

  constexpr T &operator[](UInt32 pos);
  constexpr const T &operator[](UInt32 pos) const;
  constexpr T &operator()(UInt32 pos) { return (*this)[pos]; }
  constexpr const T &operator()(UInt32 pos) const { return (*this)[pos]; }
  constexpr T *data() { return elements.data(); }
  constexpr const T *data() const { return elements.data(); }

  // Static member variables
  constexpr UInt32 size() { return elements.size(); }

  // Relational operators
  template <typename U>
  friend constexpr bool operator==(const Vector<4, U> &va,
                                   const Vector<4, U> &vb);
  template <typename U>
  friend constexpr bool operator!=(const Vector<4, U> &va,
                                   const Vector<4, U> &vb);

  std::tuple<T, T, T, T> toTuple() const { return {x(), y(), z(), w()}; }
};

// Predefined types
using Vector4F = Vector<4, float>;
using Vector4I = Vector<4, Int32>;
using Vector4UI = Vector<4, UInt32>;
using Vector4B = Vector<4, bool>;
using Vector4D = Vector<4, double>;
using Vector4L = Vector<4, Int64>;
using Vector4UL = Vector<4, UInt64>;
using Vector4U = Vector4UI;

// Non-member operators
template <typename T>
inline constexpr Vector<4, T> operator+(const Vector<4, T> &va,
                                        const Vector<4, T> &vb);

template <typename T>
inline constexpr Vector<4, T> operator-(const Vector<4, T> &v);

template <typename T>
inline constexpr Vector<4, T> operator-(const Vector<4, T> &va,
                                        const Vector<4, T> &vb);

template <typename T>
inline constexpr Vector<4, T> operator*(const Vector<4, T> &va,
                                        const Vector<4, T> &vb);

template <typename T>
inline constexpr Vector<4, T> operator*(const Vector<4, T> &va,
                                        const Vector<1, T> &vb);

template <typename T>
inline constexpr Vector<4, T> operator*(const Vector<1, T> &va,
                                        const Vector<4, T> &vb);

template <typename T>
inline constexpr Vector<4, T> operator*(const T &scalar, const Vector<4, T> &v);

template <typename T>
inline constexpr Vector<4, T> operator*(const Vector<4, T> &v, const T &scalar);

template <typename T>
inline constexpr Vector<4, T> operator/(const Vector<4, T> &v, const T &scalar);

// Vector operations
template <typename T>
inline T dot(const Vector<4, T> &va, const Vector<4, T> &vb);

template <typename T>
inline T norm(const Vector<4, T> &v);

template <typename T>
inline Vector<4, T> normalize(const Vector<4, T> &v);
}  // namespace Neat

#include "Math/Types/Vector4.inl"