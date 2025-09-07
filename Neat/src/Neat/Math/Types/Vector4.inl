#include "Neat/Math/Exponential.hpp"

namespace Neat {
// Default constructor
template <typename T>
constexpr Vector<4, T>::Vector()
    : elements{zero<T>, zero<T>, zero<T>, zero<T>} {}

// Basic Constructors
template <typename T>
inline constexpr Vector<4, T>::Vector(const T &scalar)
    : elements{scalar, scalar, scalar, scalar} {}

template <typename T>
inline constexpr Vector<4, T>::Vector(const T &x, const T &y, const T &z,
                                      const T &w)
    : elements{x, y, z, w} {}

template <typename T>
inline constexpr Vector<4, T>::Vector(const std::array<T, 4> &data)
    : elements{data} {}

// Copy Constructor
template <typename T>
inline constexpr Vector<4, T>::Vector(const Vector<4, T> &v)
    : elements{v.elements} {}

// Conversion constructors
template <typename T>
template <typename U>
inline constexpr Vector<4, T>::Vector(const Vector<4, U> &v)
    : elements{static_cast<T>(v.x()), static_cast<T>(v.y()),
               static_cast<T>(v.z()), static_cast<T>(v.w())} {}

template <typename T>
template <typename U>
inline constexpr Vector<4, T>::Vector(const Vector<3, U> &v)
    : elements{static_cast<T>(v.x()), static_cast<T>(v.y()),
               static_cast<T>(v.z()), zero<T>} {}

template <typename T>
template <typename U>
inline constexpr Vector<4, T>::Vector(const Vector<2, U> &v)
    : elements{static_cast<T>(v.x()), static_cast<T>(v.y()), zero<T>, zero<T>} {
}

template <typename T>
template <typename U>
inline constexpr Vector<4, T>::Vector(const Vector<1, U> &v)
    : elements{static_cast<T>(v.x()), zero<T>, zero<T>, zero<T>} {}

template <typename T>
template <typename A, typename B>
inline constexpr Vector<4, T>::Vector(const Vector<3, A> &v, const B &scalar)
    : elements{static_cast<T>(v.x()), static_cast<T>(v.y()),
               static_cast<T>(v.z()), static_cast<T>(scalar)} {}

template <typename T>
template <typename A, typename B, typename C>
inline constexpr Vector<4, T>::Vector(const Vector<2, A> &v, const B &scalar1,
                                      const C &scalar2)
    : elements{static_cast<T>(v.x()), static_cast<T>(v.y()),
               static_cast<T>(scalar1), static_cast<T>(scalar2)} {}

template <typename T>
template <typename A, typename B, typename C, typename D>
inline constexpr Vector<4, T>::Vector(const Vector<1, A> &v, const B &scalar1,
                                      const C &scalar2, const D &scalar3)
    : elements{static_cast<T>(v.x()), static_cast<T>(scalar1),
               static_cast<T>(scalar2), static_cast<T>(scalar3)} {}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
inline constexpr Vector<4, T>::Vector(const X &x, const Y &y, const Z &z,
                                      const W &w)
    : elements{static_cast<T>(x), static_cast<T>(y), static_cast<T>(z),
               static_cast<T>(w)} {}

template <typename T>
inline constexpr Vector<4, T>::Vector(const T *data, UInt32 count) {
  if (count > size()) {
    count = size();
  }

  std::copy(data, data + count, elements.data());
  std::fill(elements.data() + count, elements.data() + size(), zero<T>);
}

// Assignment operators
template <typename T>
template <typename U>
inline constexpr Vector<4, T> &Vector<4, T>::operator=(
    const Vector<4, U> &other) {
  x() = other.x();
  y() = other.y();
  z() = other.z();
  w() = other.w();

  return *this;
}

// Compound assigment operators
template <typename T>
template <typename U>
inline constexpr Vector<4, T> &Vector<4, T>::operator+=(const Vector<4, U> &v) {
  x() += v.x();
  y() += v.y();
  z() += v.z();
  w() += v.w();

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<4, T> &Vector<4, T>::operator-=(const Vector<4, U> &v) {
  x() -= v.x();
  y() -= v.y();
  z() -= v.z();
  w() -= v.w();

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<4, T> &Vector<4, T>::operator*=(const Vector<4, U> &v) {
  x() *= v.x();
  y() *= v.y();
  z() *= v.z();
  w() *= v.w();

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<4, T> &Vector<4, T>::operator*=(const U &scalar) {
  x() *= scalar;
  y() *= scalar;
  z() *= scalar;
  w() *= scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<4, T> &Vector<4, T>::operator/=(const U &scalar) {
  x() /= static_cast<T>(scalar);
  y() /= static_cast<T>(scalar);
  z() /= static_cast<T>(scalar);
  w() /= static_cast<T>(scalar);

  return *this;
}

template <typename T>
inline constexpr Vector<4, T>::operator bool() const {
  if constexpr (std::is_same_v<T, bool>) {
    return x() and y() and z() and w();
  } else {
    return (norm(*this) > zero<T>);
  }
}

template <typename T>
inline constexpr T &Vector<4, T>::operator[](UInt32 pos) {
  return elements[pos];
}

template <typename T>
inline constexpr const T &Vector<4, T>::operator[](UInt32 pos) const {
  return elements[pos];
}

// Non member operators
template <typename T>
inline constexpr Vector<4, T> operator+(const Vector<4, T> &va,
                                        const Vector<4, T> &vb) {
  return Vector<4, T>{va} += vb;
}

template <typename T>
inline constexpr Vector<4, T> operator-(const Vector<4, T> &v) {
  return Vector<4, T>{-v.x(), -v.y(), -v.z(), -v.w()};
}

template <typename T>
inline constexpr Vector<4, T> operator-(const Vector<4, T> &va,
                                        const Vector<4, T> &vb) {
  return Vector<4, T>{va} -= vb;
}

template <typename T>
inline constexpr Vector<4, T> operator*(const Vector<4, T> &va,
                                        const Vector<4, T> &vb) {
  return Vector<4, T>{va} *= vb;
}

template <typename T>
inline constexpr Vector<4, T> operator*(const Vector<4, T> &va,
                                        const Vector<1, T> &vb) {
  return Vector<4, T>{va} *= vb.x();
}

template <typename T>
inline constexpr Vector<4, T> operator*(const Vector<1, T> &va,
                                        const Vector<4, T> &vb) {
  return Vector<4, T>{vb} *= va.x();
}

template <typename T>
inline constexpr Vector<4, T> operator*(const T &scalar,
                                        const Vector<4, T> &v) {
  return Vector<4, T>{v} *= scalar;
}

template <typename T>
inline constexpr Vector<4, T> operator*(const Vector<4, T> &v,
                                        const T &scalar) {
  return Vector<4, T>{v} *= scalar;
}

template <typename T>
inline constexpr Vector<4, T> operator/(const Vector<4, T> &v,
                                        const T &scalar) {
  return Vector<4, T>{v} /= scalar;
}

// Relational operators
template <typename U>
inline constexpr bool operator==(const Vector<4, U> &va,
                                 const Vector<4, U> &vb) {
  return va.elements == vb.elements;
}

template <typename U>
inline constexpr bool operator!=(const Vector<4, U> &va,
                                 const Vector<4, U> &vb) {
  return not(va == vb);
}

// Output stream operator
template <typename T>
inline constexpr std::ostream &operator<<(std::ostream &os,
                                          const Vector<4, T> &v) {
  return os << "Vector4<" << typeid(T).name() << ">{" << v.x() << ", " << v.y()
            << ", " << v.z() << ", " << v.w() << "}";
}

// Vector operations
template <typename T>
T dot(const Vector<4, T> &va, const Vector<4, T> &vb) {
  return va.x() * vb.x() + va.y() * vb.y() + va.z() * vb.z() + va.w() * vb.w();
}

template <typename T>
T norm(const Vector<4, T> &v) {
  return sqrt(dot(v, v));
}

template <typename T>
Vector<4, T> normalize(const Vector<4, T> &v) {
  T one_over_norm = one<T> / norm(v);

  return one_over_norm * v;
}
}  // namespace Neat