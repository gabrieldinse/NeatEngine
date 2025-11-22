#include "Math/Exponential.hpp"
#include "Core/Assert.hpp"

namespace Neat {
// Default constructor
template <typename T>
inline constexpr Vector<1, T>::Vector() : elements{Zero<T>} {}

// Basic Constructors
template <typename T>
inline constexpr Vector<1, T>::Vector(const T &scalar) : elements{scalar} {}

template <typename T>
inline constexpr Vector<1, T>::Vector(const std::array<T, 1> &data)
    : elements{data} {}

// Copy Constructor
template <typename T>
inline constexpr Vector<1, T>::Vector(const Vector<1, T> &v)
    : elements{v.elements} {}

// Conversion constructors
template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const Vector<1, U> &v)
    : elements{static_cast<T>(v.x())} {}

template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const Vector<4, U> &v)
    : elements{static_cast<T>(v.x())} {}

template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const Vector<3, U> &v)
    : elements{static_cast<T>(v.x())} {}

template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const Vector<2, U> &v)
    : elements{static_cast<T>(v.x())} {}

template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const U &x)
    : elements{static_cast<T>(x)} {}

// Assignment operators
template <typename T>
inline constexpr Vector<1, T> &Vector<1, T>::operator=(const T &scalar) {
  elements[0] = scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator=(
    const Vector<1, U> &other) {
  x() = static_cast<T>(other.x());

  return *this;
}

// Compound assignment operators
template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator+=(const Vector<1, U> &v) {
  x() += static_cast<T>(v.x());

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator-=(const Vector<1, U> &v) {
  x() -= static_cast<T>(v.x());

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator*=(const Vector<1, U> &v) {
  x() *= static_cast<T>(v.x());

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator*=(const U &scalar) {
  x() *= static_cast<T>(scalar);

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator/=(const U &scalar) {
  NT_CORE_ASSERT(scalar != Zero<T>,
                 "Division by zero in vector-scalar division.");
  x() /= static_cast<T>(scalar);

  return *this;
}

template <typename T>
inline constexpr Vector<1, T>::operator bool() const {
  if constexpr (std::is_same_v<T, bool>) {
    return x();
  } else {
    return (std::fabs(x()) > Zero<T>);
  }
}

template <typename T>
inline constexpr T &Vector<1, T>::operator[](UInt32 pos) {
  NT_CORE_ASSERT(pos < N);

  return elements[pos];
}

template <typename T>
inline constexpr const T &Vector<1, T>::operator[](UInt32 pos) const {
  NT_CORE_ASSERT(pos < N);

  return elements[pos];
}

// Non member operators
template <typename T>
inline constexpr Vector<1, T> operator+(const Vector<1, T> &va,
                                        const Vector<1, T> &vb) {
  return Vector<1, T>(va) += vb;
}

template <typename T>
inline constexpr Vector<1, T> operator-(const Vector<1, T> &v) {
  return Vector<1, T>(-v.x());
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
  NT_CORE_ASSERT(scalar != Zero<T>,
                 "Division by zero in vector-scalar division.");
  return Vector<1, T>(v) /= scalar;
}

// Relational operators
template <typename U>
inline constexpr bool operator==(const Vector<1, U> &va,
                                 const Vector<1, U> &vb) {
  return va.elements == vb.elements;
}

template <typename U>
inline constexpr bool operator!=(const Vector<1, U> &va,
                                 const Vector<1, U> &vb) {
  return not(va == vb);
}

// Vector operations
template <typename T>
T dot(const Vector<1, T> &va, const Vector<1, T> &vb) {
  return va.x() * vb.x();
}

template <typename T>
T norm(const Vector<1, T> &v) {
  return abs(v.x());
}

template <typename T>
Vector<1, T> normalize(const Vector<1, T> &v) {
  T one_over_norm = One<T> / norm(v);

  return one_over_norm * v;
}
}  // namespace Neat