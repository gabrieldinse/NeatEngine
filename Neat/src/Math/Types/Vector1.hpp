#pragma once

#include <cmath>
#include <type_traits>
#include <array>
#include <tuple>

#include "TypeVectorN.hpp"

#include "Core/Assert.hpp"

namespace Neat {
template <typename T>
struct Vector<1, T> {
  using Type = Vector<1, T>;
  using ValueType = T;
  static constexpr UInt32 N = 1;

  std::array<T, 1> elements;

  // Default constructor
  constexpr Vector();

  // Basic Constructors
  constexpr explicit Vector(const T &scalar);
  constexpr Vector(const std::array<T, 1> &data);

  // Copy Constructor
  constexpr Vector(const Vector<1, T> &v);

  // Conversion constructors
  template <typename U>
  constexpr explicit Vector(const Vector<1, U> &v);
  template <typename U>
  constexpr explicit Vector(const Vector<4, U> &v);
  template <typename U>
  constexpr explicit Vector(const Vector<3, U> &v);
  template <typename U>
  constexpr explicit Vector(const Vector<2, U> &v);
  template <typename U>
  constexpr Vector(const U &x);

  // Assignment operators
  constexpr Vector<1, T> &operator=(const T &scalar);
  constexpr Vector<1, T> &operator=(const Vector<1, T> &other) = default;
  template <typename U>
  constexpr Vector<1, T> &operator=(const Vector<1, U> &other);

  // Compound assignment operators
  template <typename U>
  constexpr Vector<1, T> &operator+=(const Vector<1, U> &v);
  template <typename U>
  constexpr Vector<1, T> &operator-=(const Vector<1, U> &v);
  template <typename U>
  constexpr Vector<1, T> &operator*=(const Vector<1, U> &v);
  template <typename U>
  constexpr Vector<1, T> &operator*=(const U &scalar);
  template <typename U>
  constexpr Vector<1, T> &operator/=(const U &scalar);

  // Explicit conversion operators
  inline constexpr explicit operator bool() const;

  // Element acessing
  constexpr T &x() { return elements[0]; }
  constexpr const T &x() const { return elements[0]; }

  constexpr T &r() { return x(); }
  constexpr const T &r() const { return x(); }

  constexpr T &i() { return x(); }
  constexpr const T &i() const { return x(); }

  constexpr T &s() { return x(); }
  constexpr const T &s() const { return x(); }

  constexpr T &operator[](UInt32 pos);
  constexpr const T &operator[](UInt32 pos) const;
  constexpr T &operator()(UInt32 pos) { return (*this)[pos]; }
  constexpr const T &operator()(UInt32 pos) const { return (*this)[pos]; }
  constexpr T *data() { return elements.data(); }
  constexpr const T *data() const { return elements.data(); }

  constexpr UInt32 size() { return elements.size(); }

  // Relational operators
  template <typename U>
  friend constexpr bool operator==(const Vector<1, U> &va,
                                   const Vector<1, U> &vb);
  template <typename U>
  friend constexpr bool operator!=(const Vector<1, U> &va,
                                   const Vector<1, U> &vb);

  std::tuple<T> toTuple() const { return {x()}; }
};

// Predefined types
using Vector1F = Vector<1, float>;
using Vector1I = Vector<1, Int32>;
using Vector1UI = Vector<1, UInt32>;
using Vector1B = Vector<1, bool>;
using Vector1D = Vector<1, double>;
using Vector1U = Vector1UI;

// Nom member operators
template <typename T>
inline constexpr Vector<1, T> operator+(const Vector<1, T> &va,
                                        const Vector<1, T> &vb);

template <typename T>
inline constexpr Vector<1, T> operator-(const Vector<1, T> &v);

template <typename T>
inline constexpr Vector<1, T> operator-(const Vector<1, T> &va,
                                        const Vector<1, T> &vb);

template <typename T>
inline constexpr Vector<1, T> operator*(const Vector<1, T> &va,
                                        const Vector<1, T> &vb);

template <typename T>
inline constexpr Vector<1, T> operator*(const T &scalar, const Vector<1, T> &v);

template <typename T>
inline constexpr Vector<1, T> operator*(const Vector<1, T> &v, const T &scalar);

template <typename T>
inline constexpr Vector<1, T> operator/(const Vector<1, T> &v, const T &scalar);

// Vector operations
template <typename T>
inline T dot(const Vector<1, T> &va, const Vector<1, T> &vb);

template <typename T>
inline T norm(const Vector<1, T> &v);

template <typename T>
inline Vector<1, T> normalize(const Vector<1, T> &v);
}  // namespace Neat

#include "Math/Types/Vector1.inl"
