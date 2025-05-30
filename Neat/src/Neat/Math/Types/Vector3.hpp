#pragma once

#include <type_traits>

#include "Neat/Math/Types/TypeVectorN.hpp"

namespace Neat {
template <typename T>
struct Vector<3, T> {
  using Type = Vector<3, T>;
  using ValueType = T;

  // Class Data
  union {
    struct {
      T x, y, z;
    };
    struct {
      T r, g, b;
    };
    struct {
      T i, j, k;
    };
    struct {
      T s, t, p;
    };
  };

  // Default constructor
  constexpr Vector();

  // Basic Constructors
  constexpr explicit Vector(const T &scalar);
  constexpr Vector(const T &x, const T &y, const T &z);

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
  constexpr T &operator[](UInt32 pos);
  constexpr const T &operator[](UInt32 pos) const;
  constexpr T &operator()(UInt32 pos) { return (*this)[pos]; }
  constexpr const T &operator()(UInt32 pos) const { return (*this)[pos]; }
  constexpr T *dataPointer() { return &x; }
  constexpr const T *dataPointer() const { return &x; }

  // Static member variables
  constexpr static UInt32 size() { return 3; }
  static constexpr UInt32 length() { return size(); }
};

// Predefined types
using Vector3F = Vector<3, float>;
using Vector3I = Vector<3, Int32>;
using Vector3UI = Vector<3, UInt32>;
using Vector3B = Vector<3, bool>;
using Vector3D = Vector<3, double>;

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

// Relational operators
template <typename T>
inline constexpr bool operator==(const Vector<3, T> &va,
                                 const Vector<3, T> &vb);

template <typename T>
inline constexpr bool operator!=(const Vector<3, T> &va,
                                 const Vector<3, T> &vb);

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