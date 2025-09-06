#pragma once

#include <type_traits>

#include "Neat/Math/Types/TypeVectorN.hpp"

namespace Neat {
template <typename T>
struct Vector<3, T> {
  using Type = Vector<3, T>;
  using ValueType = T;

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
  constexpr T &x() { return m_data[0]; }
  constexpr const T &x() const { return m_data[0]; }
  constexpr T &y() { return m_data[1]; }
  constexpr const T &y() const { return m_data[1]; }
  constexpr T &z() { return m_data[2]; }
  constexpr const T &z() const { return m_data[2]; }

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
  constexpr T *data() { return m_data.data(); }
  constexpr const T *data() const { return m_data.data(); }

  // Static member variables
  constexpr UInt32 size() { return m_data.size(); }

  // Relational operators
  template <typename U>
  friend constexpr bool operator==(const Vector<3, U> &va,
                                   const Vector<3, U> &vb);
  template <typename U>
  friend constexpr bool operator!=(const Vector<3, U> &va,
                                   const Vector<3, U> &vb);

 private:
  std::array<T, 3> m_data;
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

// Output stream operator
template <typename T>
inline constexpr std::ostream &operator<<(std::ostream &os,
                                          const Vector<3, T> &v);

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