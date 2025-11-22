#include "Math/Exponential.hpp"
#include "Core/Assert.hpp"

namespace Neat {
// Default constructor
template <typename T>
inline constexpr Vector<2, T>::Vector() : elements{Zero<T>, Zero<T>} {}

// Basic Constructors
template <typename T>
inline constexpr Vector<2, T>::Vector(const T &scalar)
    : elements{scalar, scalar} {}

template <typename T>
inline constexpr Vector<2, T>::Vector(const T &x, const T &y)
    : elements{x, y} {}

template <typename T>
inline constexpr Vector<2, T>::Vector(const std::array<T, 2> &data)
    : elements{data} {}

// Copy Constructor
template <typename T>
inline constexpr Vector<2, T>::Vector(const Vector<2, T> &v)
    : elements{v.elements} {}

// Conversion constructors
template <typename T>
template <typename U>
inline constexpr Vector<2, T>::Vector(const Vector<2, U> &v)
    : elements{static_cast<T>(v.x()), static_cast<T>(v.y())} {}

template <typename T>
template <typename U>
inline constexpr Vector<2, T>::Vector(const Vector<4, U> &v)
    : elements{static_cast<T>(v.x()), static_cast<T>(v.y())} {}

template <typename T>
template <typename U>
inline constexpr Vector<2, T>::Vector(const Vector<3, U> &v)
    : elements{static_cast<T>(v.x()), static_cast<T>(v.y())} {}

template <typename T>
template <typename U>
inline constexpr Vector<2, T>::Vector(const Vector<1, U> &v)
    : elements{static_cast<T>(v.x()), Zero<T>} {}

template <typename T>
template <typename A, typename B>
inline constexpr Vector<2, T>::Vector(const Vector<1, A> &v, const B &scalar1)
    : elements{static_cast<T>(v.x()), static_cast<T>(scalar1)} {}

template <typename T>
template <typename X, typename Y>
inline constexpr Vector<2, T>::Vector(const X &x, const Y &y)
    : elements{static_cast<T>(x), static_cast<T>(y)} {}

template <typename T>
inline constexpr Vector<2, T>::Vector(const T *data, UInt32 count) {
  if (count > size()) {
    count = size();
  }

  std::copy(data, data + count, elements.data());
  std::fill(elements.data() + count, elements.data() + size(), Zero<T>);
}

// Assignment operators
template <typename T>
template <typename U>
inline constexpr Vector<2, T> &Vector<2, T>::operator=(
    const Vector<2, U> &other) {
  x() = static_cast<T>(other.x());
  y() = static_cast<T>(other.y());

  return *this;
}

// Compound assignment operators
template <typename T>
template <typename U>
inline constexpr Vector<2, T> &Vector<2, T>::operator+=(const Vector<2, U> &v) {
  x() += static_cast<T>(v.x());
  y() += static_cast<T>(v.y());

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<2, T> &Vector<2, T>::operator-=(const Vector<2, U> &v) {
  x() -= static_cast<T>(v.x());
  y() -= static_cast<T>(v.y());

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<2, T> &Vector<2, T>::operator*=(const Vector<2, U> &v) {
  x() *= static_cast<T>(v.x());
  y() *= static_cast<T>(v.y());

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<2, T> &Vector<2, T>::operator*=(const U &scalar) {
  x() *= static_cast<T>(scalar);
  y() *= static_cast<T>(scalar);

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<2, T> &Vector<2, T>::operator/=(const U &scalar) {
  x() /= static_cast<T>(scalar);
  y() /= static_cast<T>(scalar);

  return *this;
}

template <typename T>
inline constexpr Vector<2, T>::operator bool() const {
  if constexpr (std::is_same_v<T, bool>) {
    return x() and y();
  } else {
    return (norm(*this) > Zero<T>);
  }
}

template <typename T>
inline constexpr T &Vector<2, T>::operator[](UInt32 pos) {
  NT_CORE_ASSERT(pos < N);

  return elements[pos];
}

template <typename T>
inline constexpr const T &Vector<2, T>::operator[](UInt32 pos) const {
  NT_CORE_ASSERT(pos < N);

  return elements[pos];
}

// Non member operators
template <typename T>
inline constexpr Vector<2, T> operator+(const Vector<2, T> &va,
                                        const Vector<2, T> &vb) {
  return Vector<2, T>{va} += vb;
}

template <typename T>
inline constexpr Vector<2, T> operator-(const Vector<2, T> &v) {
  return Vector<2, T>{-v.x(), -v.y()};
}

template <typename T>
inline constexpr Vector<2, T> operator-(const Vector<2, T> &va,
                                        const Vector<2, T> &vb) {
  return Vector<2, T>{va} -= vb;
}

template <typename T>
inline constexpr Vector<2, T> operator*(const Vector<2, T> &va,
                                        const Vector<2, T> &vb) {
  return Vector<2, T>(va) *= vb;
}

template <typename T>
inline constexpr Vector<2, T> operator*(const Vector<2, T> &va,
                                        const Vector<1, T> &vb) {
  return Vector<2, T>{va} *= vb.x();
}

template <typename T>
inline constexpr Vector<2, T> operator*(const Vector<1, T> &va,
                                        const Vector<2, T> &vb) {
  return Vector<2, T>{vb} *= va.x();
}

template <typename T>
inline constexpr Vector<2, T> operator*(const T &scalar,
                                        const Vector<2, T> &v) {
  return Vector<2, T>{v} *= scalar;
}

template <typename T>
inline constexpr Vector<2, T> operator*(const Vector<2, T> &v,
                                        const T &scalar) {
  return Vector<2, T>{v} *= scalar;
}

template <typename T>
inline constexpr Vector<2, T> operator/(const Vector<2, T> &v,
                                        const T &scalar) {
  return Vector<2, T>{v} /= scalar;
}

// Relational operators
template <typename U>
inline constexpr bool operator==(const Vector<2, U> &va,
                                 const Vector<2, U> &vb) {
  return va.elements == vb.elements;
}

template <typename U>
inline constexpr bool operator!=(const Vector<2, U> &va,
                                 const Vector<2, U> &vb) {
  return not(va == vb);
}

// Vector operations
template <typename T>
T dot(const Vector<2, T> &va, const Vector<2, T> &vb) {
  return va.x() * vb.x() + va.y() * vb.y();
}

template <typename T>
T norm(const Vector<2, T> &v) {
  return sqrt(dot(v, v));
}

template <typename T>
Vector<2, T> normalize(const Vector<2, T> &v) {
  T one_over_norm = static_cast<T>(1) / norm(v);

  return one_over_norm * v;
}
}  // namespace Neat