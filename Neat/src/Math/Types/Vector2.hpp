#pragma once

#include <type_traits>
#include <array>
#include <tuple>

#include "TypeVectorN.hpp"

#include "Core/Assert.hpp"

namespace Neat {
template <typename T>
struct Vector<2, T> {
  using Type = Vector<2, T>;
  using ValueType = T;
  static constexpr UInt32 N = 2;

  std::array<T, 2> elements;

  // Default constructor
  constexpr Vector();

  // Basic Constructors
  constexpr explicit Vector(const T &scalar);
  constexpr Vector(const T &x, const T &y);
  constexpr Vector(const std::array<T, 2> &data);

  // Copy Constructor
  constexpr Vector(const Vector<2, T> &v);

  // Conversion constructors
  template <typename U>
  constexpr explicit Vector(const Vector<2, U> &v);
  template <typename U>
  constexpr explicit Vector(const Vector<4, U> &v);
  template <typename U>
  constexpr explicit Vector(const Vector<3, U> &v);
  template <typename U>
  constexpr explicit Vector(const Vector<1, U> &v);
  template <typename A, typename B>
  constexpr explicit Vector(const Vector<1, A> &v, const B &scalar1);
  template <typename X, typename Y>
  constexpr Vector(const X &x, const Y &y);

  constexpr Vector(const T *data, UInt32 count);

  // Assignment operators
  constexpr Vector<2, T> &operator=(const Vector<2, T> &other) = default;
  template <typename U>
  constexpr Vector<2, T> &operator=(const Vector<2, U> &other);

  // Compound assignment operators
  template <typename U>
  constexpr Vector<2, T> &operator+=(const Vector<2, U> &v);
  template <typename U>
  constexpr Vector<2, T> &operator-=(const Vector<2, U> &v);
  template <typename U>
  constexpr Vector<2, T> &operator*=(const Vector<2, U> &v);
  template <typename U>
  constexpr Vector<2, T> &operator*=(const Vector<1, U> &v);
  template <typename U>
  constexpr Vector<2, T> &operator*=(const U &scalar);
  template <typename U>
  constexpr Vector<2, T> &operator/=(const U &scalar);

  // Explicit conversion operators
  inline constexpr explicit operator bool() const;

  // Element acessing
  constexpr T &x() { return elements[0]; }
  constexpr const T &x() const { return elements[0]; }
  constexpr T &y() { return elements[1]; }
  constexpr const T &y() const { return elements[1]; }

  constexpr T &r() { return x(); }
  constexpr const T &r() const { return x(); }
  constexpr T &g() { return y(); }
  constexpr const T &g() const { return y(); }

  constexpr T &i() { return x(); }
  constexpr const T &i() const { return x(); }
  constexpr T &j() { return y(); }
  constexpr const T &j() const { return y(); }

  constexpr T &s() { return x(); }
  constexpr const T &s() const { return x(); }
  constexpr T &t() { return y(); }
  constexpr const T &t() const { return y(); }

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
  friend constexpr bool operator==(const Vector<2, U> &va,
                                   const Vector<2, U> &vb);
  template <typename U>
  friend constexpr bool operator!=(const Vector<2, U> &va,
                                   const Vector<2, U> &vb);

  std::tuple<T, T> toTuple() const { return {x(), y()}; }
};

// Predefined types
using Vector2F = Vector<2, float>;
using Vector2I = Vector<2, Int32>;
using Vector2UI = Vector<2, UInt32>;
using Vector2B = Vector<2, bool>;
using Vector2D = Vector<2, double>;
using Vector2L = Vector<2, Int64>;
using Vector2UL = Vector<2, UInt64>;
using Vector2U = Vector2UI;

// Nom member operators
template <typename T>
inline constexpr Vector<2, T> operator+(const Vector<2, T> &va,
                                        const Vector<2, T> &vb);

template <typename T>
inline constexpr Vector<2, T> operator-(const Vector<2, T> &v);

template <typename T>
inline constexpr Vector<2, T> operator-(const Vector<2, T> &va,
                                        const Vector<2, T> &vb);

template <typename T>
inline constexpr Vector<2, T> operator*(const Vector<2, T> &va,
                                        const Vector<2, T> &vb);

template <typename T>
inline constexpr Vector<2, T> operator*(const Vector<2, T> &va,
                                        const Vector<1, T> &vb);

template <typename T>
inline constexpr Vector<2, T> operator*(const T &scalar, const Vector<2, T> &v);

template <typename T>
inline constexpr Vector<2, T> operator*(const Vector<2, T> &v, const T &scalar);

template <typename T>
inline constexpr Vector<2, T> operator/(const Vector<2, T> &v, const T &scalar);

// Vector operations
template <typename T>
inline T dot(const Vector<2, T> &va, const Vector<2, T> &vb);

template <typename T>
inline T norm(const Vector<2, T> &v);

template <typename T>
inline Vector<2, T> normalize(const Vector<2, T> &v);
}  // namespace Neat

#include "Math/Types/Vector2.inl"
