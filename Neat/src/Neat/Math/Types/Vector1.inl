#include "Neat/Math/Exponential.hpp"

namespace Neat {
// Default constructor
template <typename T>
inline constexpr Vector<1, T>::Vector() : x(zero<T>) {}

// Basic Constructors
template <typename T>
inline constexpr Vector<1, T>::Vector(const T &scalar) : x(scalar) {}

// Copy Constructor
template <typename T>
inline constexpr Vector<1, T>::Vector(const Vector<1, T> &v) : x(v.x) {}

// Conversion constructors
template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const Vector<1, U> &v)
    : x(static_cast<T>(v.x)) {}

template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const Vector<4, U> &v)
    : x(static_cast<T>(v.x)) {}

template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const Vector<3, U> &v)
    : x(static_cast<T>(v.x)) {}

template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const Vector<2, U> &v)
    : x(static_cast<T>(v.x)) {}

template <typename T>
template <typename X>
inline constexpr Vector<1, T>::Vector(const X &x) : x(static_cast<T>(x)) {}

// Assignment operators
template <typename T>
inline constexpr Vector<1, T> &Vector<1, T>::operator=(const T &scalar) {
  x = scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator=(
    const Vector<1, U> &other) {
  x = other.x;

  return *this;
}

// Compound assignment operators
template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator+=(const Vector<1, U> &v) {
  x += v.x;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator-=(const Vector<1, U> &v) {
  x -= v.x;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator*=(const Vector<1, U> &v) {
  x *= v.x;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator*=(const U &scalar) {
  x *= scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator/=(const U &scalar) {
  x /= scalar;

  return *this;
}

template <typename T>
inline constexpr Vector<1, T>::operator bool() const {
  if constexpr (std::is_same_v<T, bool>) {
    return x;
  } else {
    return (std::fabs(x) > zero<T>);
  }
}

template <typename T>
inline constexpr T &Vector<1, T>::operator[](UInt32 pos) {
  return (&x)[pos];
}

template <typename T>
inline constexpr const T &Vector<1, T>::operator[](UInt32 pos) const {
  return (&x)[pos];
}

// Non member operators
template <typename T>
inline constexpr Vector<1, T> operator+(const Vector<1, T> &va,
                                        const Vector<1, T> &vb) {
  return Vector<1, T>(va) += vb;
}

template <typename T>
inline constexpr Vector<1, T> operator-(const Vector<1, T> &v) {
  return Vector<1, T>(-v.x);
}

template <typename T>
inline constexpr Vector<1, T> operator-(const Vector<1, T> &va,
                                        const Vector<1, T> &vb) {
  return Vector<1, T>(va) -= vb;
}

template <typename T>
inline constexpr Vector<1, T> operator*(const Vector<1, T> &va,
                                        const Vector<1, T> &vb) {
  return Vector<1, T>(va) *= vb;
}

template <typename T>
inline constexpr Vector<1, T> operator*(const T &scalar,
                                        const Vector<1, T> &v) {
  return Vector<1, T>(v) *= scalar;
}

template <typename T>
inline constexpr Vector<1, T> operator*(const Vector<1, T> &v,
                                        const T &scalar) {
  return Vector<1, T>(v) *= scalar;
}

template <typename T>
inline constexpr Vector<1, T> operator/(const Vector<1, T> &v,
                                        const T &scalar) {
  return Vector<1, T>(v) /= scalar;
}

// Relational operators
template <typename T>
inline constexpr bool operator==(const Vector<1, T> &va,
                                 const Vector<1, T> &vb) {
  return va.x == vb.x;
}

template <typename T, UInt32 N>
inline constexpr bool operator!=(const Vector<1, T> &va,
                                 const Vector<1, T> &vb) {
  return not(va == vb);
}

// Output stream operator
template <typename T>
inline constexpr std::ostream &operator<<(std::ostream &os,
                                          const Vector<1, T> &v) {
  return os << "Vector1<" << typeid(T).name() << ">{" << v.x << "}";
}

// Vector operations
template <typename T>
T dot(const Vector<1, T> &va, const Vector<1, T> &vb) {
  return va.x * vb.x;
}

template <typename T>
T norm(const Vector<1, T> &v) {
  return abs(v.x);
}

template <typename T>
Vector<1, T> normalize(const Vector<1, T> &v) {
  T one_over_norm = one<T> / norm(v);

  return one_over_norm * v;
}
}  // namespace Neat