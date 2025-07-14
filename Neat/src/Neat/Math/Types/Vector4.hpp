#pragma once

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
struct Vector<4, T> {
  using Type = Vector<4, T>;
  using ValueType = T;

  // Class Data
  union {
    struct {
      T x, y, z, w;
    };
    struct {
      T r, g, b, a;
    };
    struct {
      T i, j, k, l;
    };
    struct {
      T s, t, p, q;
    };
  };

  // Default constructor
  constexpr Vector();

  // Basic Constructors
  constexpr explicit Vector(const T &scalar);

  constexpr Vector(const T &x, const T &y, const T &z, const T &w);

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
  constexpr Vector<4, T> &operator*=(const Vector<1, U> &v);
  template <typename U>
  constexpr Vector<4, T> &operator*=(const U &scalar);
  template <typename U>
  constexpr Vector<4, T> &operator/=(const U &scalar);

  // Explicit conversion operators
  constexpr explicit operator bool() const;

  // Element acessing
  constexpr T &operator[](UInt32 pos);
  constexpr const T &operator[](UInt32 pos) const;
  constexpr T &operator()(UInt32 pos) { return (*this)[pos]; }
  constexpr const T &operator()(UInt32 pos) const { return (*this)[pos]; }
  constexpr T *dataPointer() { return &x; }
  constexpr const T *dataPointer() const { return &x; }

  // Static member variables
  static constexpr UInt32 size() { return 4; }
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
using Vector4F = Vector<4, float>;
using Vector4I = Vector<4, Int32>;
using Vector4UI = Vector<4, UInt32>;
using Vector4B = Vector<4, bool>;
using Vector4D = Vector<4, double>;

// Nom member operators
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

// Relational operators
template <typename T>
inline constexpr bool operator==(const Vector<4, T> &va,
                                 const Vector<4, T> &vb);

template <typename T>
inline constexpr bool operator!=(const Vector<4, T> &va,
                                 const Vector<4, T> &vb);

// Output stream operator
template <typename T>
inline constexpr std::ostream &operator<<(std::ostream &os,
                                          const Vector<4, T> &v);

// Vector operations
template <typename T>
inline T dot(const Vector<4, T> &va, const Vector<4, T> &vb);

template <typename T>
inline T norm(const Vector<4, T> &v);

template <typename T>
inline Vector<4, T> normalize(const Vector<4, T> &v);
}  // namespace Neat

#include "Neat/Math/Types/Vector4.inl"