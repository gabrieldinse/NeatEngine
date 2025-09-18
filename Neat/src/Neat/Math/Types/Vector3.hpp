#pragma once

#include <type_traits>
#include <tuple>

#include "TypeVectorN.hpp"

namespace Neat {
template <typename T>
struct Vector<3, T> {
  using Type = Vector<3, T>;
  using ValueType = T;

  std::array<T, 3> elements;

  // Default constructor
  constexpr Vector();

  // Basic Constructors
  constexpr explicit Vector(const T &scalar);
  constexpr Vector(const T &x, const T &y, const T &z);
  constexpr Vector(const std::array<T, 3> &data);

  // Copy Constructor
  constexpr Vector(const Vector<3, T> &v);

  // Conversion constructors
  template <typename U>
  constexpr explicit Vector(const Vector<3, U> &v);
  template <typename U>
  constexpr explicit Vector(const Vector<4, U> &v);
  template <typename U>
  constexpr explicit Vector(const Vector<2, U> &v);
  template <typename U>
  constexpr explicit Vector(const Vector<1, U> &v);
  template <typename A, typename B>
  constexpr explicit Vector(const Vector<2, A> &v, const B &scalar1);
  template <typename A, typename B, typename C>

  constexpr explicit Vector(const Vector<1, A> &v, const B &scalar1,
                            const C &scalar2);

  template <typename X, typename Y, typename Z>
  constexpr Vector(const X &x, const Y &y, const Z &z);

  constexpr Vector(const T *data, UInt32 count);

  // Assignment operators
  constexpr Vector<3, T> &operator=(const Vector<3, T> &other) = default;
  template <typename U>
  constexpr Vector<3, T> &operator=(const Vector<3, U> &other);

  // Compound assignment operators
  template <typename U>
  constexpr Vector<3, T> &operator+=(const Vector<3, U> &v);
  template <typename U>
  constexpr Vector<3, T> &operator-=(const Vector<3, U> &v);
  template <typename U>
  constexpr Vector<3, T> &operator*=(const Vector<3, U> &v);
  template <typename U>
  constexpr Vector<3, T> &operator*=(const Vector<1, U> &v);
  template <typename U>
  constexpr Vector<3, T> &operator*=(const U &scalar);
  template <typename U>
  constexpr Vector<3, T> &operator/=(const U &scalar);

  // Explicit conversion operators
  inline constexpr explicit operator bool() const;

  // Element acessing
  constexpr T &x() { return elements[0]; }
  constexpr const T &x() const { return elements[0]; }
  constexpr T &y() { return elements[1]; }
  constexpr const T &y() const { return elements[1]; }
  constexpr T &z() { return elements[2]; }
  constexpr const T &z() const { return elements[2]; }

  constexpr T &r() { return x(); }
  constexpr const T &r() const { return x(); }
  constexpr T &g() { return y(); }
  constexpr const T &g() const { return y(); }
  constexpr T &b() { return z(); }
  constexpr const T &b() const { return z(); }

  constexpr T &i() { return x(); }
  constexpr const T &i() const { return x(); }
  constexpr T &j() { return y(); }
  constexpr const T &j() const { return y(); }
  constexpr T &k() { return z(); }
  constexpr const T &k() const { return z(); }

  constexpr T &s() { return x(); }
  constexpr const T &s() const { return x(); }
  constexpr T &t() { return y(); }
  constexpr const T &t() const { return y(); }
  constexpr T &p() { return z(); }
  constexpr const T &p() const { return z(); }

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
  friend constexpr bool operator==(const Vector<3, U> &va,
                                   const Vector<3, U> &vb);
  template <typename U>
  friend constexpr bool operator!=(const Vector<3, U> &va,
                                   const Vector<3, U> &vb);

  std::tuple<T, T, T> toTuple() const { return {x(), y(), z()}; }
};

// Predefined types
using Vector3F = Vector<3, float>;
using Vector3I = Vector<3, Int32>;
using Vector3UI = Vector<3, UInt32>;
using Vector3B = Vector<3, bool>;
using Vector3D = Vector<3, double>;
using Vector3U = Vector3UI;

// Nom member operators
template <typename T>
inline constexpr Vector<3, T> operator+(const Vector<3, T> &va,
                                        const Vector<3, T> &vb);

template <typename T>
inline constexpr Vector<3, T> operator-(const Vector<3, T> &v);

template <typename T>
inline constexpr Vector<3, T> operator-(const Vector<3, T> &va,
                                        const Vector<3, T> &vb);

template <typename T>
inline constexpr Vector<3, T> operator*(const Vector<3, T> &va,
                                        const Vector<3, T> &vb);

template <typename T>
inline constexpr Vector<3, T> operator*(const Vector<3, T> &va,
                                        const Vector<1, T> &vb);

template <typename T>
inline constexpr Vector<3, T> operator*(const T &scalar, const Vector<3, T> &v);

template <typename T>
inline constexpr Vector<3, T> operator*(const Vector<3, T> &v, const T &scalar);

template <typename T>
inline constexpr Vector<3, T> operator/(const Vector<3, T> &v, const T &scalar);

// Vector operations
template <typename T>
inline T dot(const Vector<3, T> &va, const Vector<3, T> &vb);

template <typename T>
inline Vector<3, T> cross(const Vector<3, T> &va, const Vector<3, T> &vb);

template <typename T>
inline T norm(const Vector<3, T> &v);

template <typename T>
inline Vector<3, T> normalize(const Vector<3, T> &v);
}  // namespace Neat

#include "Neat/Math/Types/Vector3.inl"