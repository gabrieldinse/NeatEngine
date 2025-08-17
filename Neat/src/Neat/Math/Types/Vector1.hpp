#pragma once

#include <cmath>
#include <type_traits>

#include "Neat/Math/Types/TypeVectorN.hpp"

namespace Neat {

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#elif defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4201)
#endif

template <typename T>
struct Vector<1, T> {
  using Type = Vector<1, T>;
  using ValueType = T;

  // Class data
  union {
    T x, r, i, s;
  };

  // Default constructor
  constexpr Vector();

  // Basic Constructors
  constexpr explicit Vector(const T &scalar);

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
  template <typename X>
  constexpr Vector(const X &x);

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
  constexpr T &operator[](UInt32 pos);
  constexpr const T &operator[](UInt32 pos) const;
  constexpr T &operator()(UInt32 pos) { return (*this)[pos]; }
  constexpr const T &operator()(UInt32 pos) const { return (*this)[pos]; }
  constexpr T *dataPointer() { return &x; }
  constexpr const T *dataPointer() const { return &x; }

  // Static member variables
  static constexpr UInt32 size() { return 1; }
  static constexpr UInt32 length() { return size(); }
};

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif

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

// Relational operators
template <typename T>
inline constexpr bool operator==(const Vector<1, T> &va,
                                 const Vector<1, T> &vb);

template <typename T>
inline constexpr bool operator!=(const Vector<1, T> &va,
                                 const Vector<1, T> &vb);

// Output stream operator
template <typename T>
inline constexpr std::ostream &operator<<(std::ostream &os,
                                          const Vector<1, T> &v);

// Vector operations
template <typename T>
inline T dot(const Vector<1, T> &va, const Vector<1, T> &vb);

template <typename T>
inline T norm(const Vector<1, T> &v);

template <typename T>
inline Vector<1, T> normalize(const Vector<1, T> &v);
}  // namespace Neat

#include "Neat/Math/Types/Vector1.inl"
