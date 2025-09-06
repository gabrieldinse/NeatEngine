#include "Neat/Math/Exponential.hpp"

namespace Neat {
// Default constructor
template <typename T>
inline constexpr Vector<2, T>::Vector() : m_data{zero<T>, zero<T>} {}

// Basic Constructors
template <typename T>
inline constexpr Vector<2, T>::Vector(const T &scalar)
    : m_data{scalar, scalar} {}

template <typename T>
inline constexpr Vector<2, T>::Vector(const T &x, const T &y) : m_data{x, y} {}

template <typename T>
inline constexpr Vector<2, T>::Vector(const std::array<T, 2> &data)
    : m_data{data} {}

// Copy Constructor
template <typename T>
inline constexpr Vector<2, T>::Vector(const Vector<2, T> &v)
    : m_data{v.m_data} {}

// Conversion constructors
template <typename T>
template <typename U>
inline constexpr Vector<2, T>::Vector(const Vector<2, U> &v)
    : m_data{static_cast<T>(v.x()), static_cast<T>(v.y())} {}

template <typename T>
template <typename U>
inline constexpr Vector<2, T>::Vector(const Vector<4, U> &v)
    : m_data{static_cast<T>(v.x()), static_cast<T>(v.y())} {}

template <typename T>
template <typename U>
inline constexpr Vector<2, T>::Vector(const Vector<3, U> &v)
    : m_data{static_cast<T>(v.x()), static_cast<T>(v.y())} {}

template <typename T>
template <typename U>
inline constexpr Vector<2, T>::Vector(const Vector<1, U> &v)
    : m_data{static_cast<T>(v.x), zero<T>} {}

template <typename T>
template <typename A, typename B>
inline constexpr Vector<2, T>::Vector(const Vector<1, A> &v, const B &scalar1)
    : m_data{static_cast<T>(v.x), static_cast<T>(scalar1)} {}

template <typename T>
template <typename X, typename Y>
inline constexpr Vector<2, T>::Vector(const X &x, const Y &y)
    : m_data{static_cast<T>(x), static_cast<T>(y)} {}

template <typename T>
inline constexpr Vector<2, T>::Vector(const T *data, UInt32 count) {
  if (count > size()) {
    count = size();
  }

  std::copy(data, data + count, m_data.data());
  std::fill(m_data.data() + count, m_data.data() + size(), zero<T>);
}

// Assignment operators
template <typename T>
template <typename U>
inline constexpr Vector<2, T> &Vector<2, T>::operator=(
    const Vector<2, U> &other) {
  x() = other.x();
  y() = other.y();

  return *this;
}

// Compound assignment operators
template <typename T>
template <typename U>
inline constexpr Vector<2, T> &Vector<2, T>::operator+=(const Vector<2, U> &v) {
  x() += v.x();
  y() += v.y();

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<2, T> &Vector<2, T>::operator-=(const Vector<2, U> &v) {
  x() -= v.x();
  y() -= v.y();

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<2, T> &Vector<2, T>::operator*=(const Vector<2, U> &v) {
  x() *= v.x();
  y() *= v.y();

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<2, T> &Vector<2, T>::operator*=(const U &scalar) {
  x() *= scalar;
  y() *= scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<2, T> &Vector<2, T>::operator/=(const U &scalar) {
  x() /= scalar;
  y() /= scalar;

  return *this;
}

template <typename T>
inline constexpr Vector<2, T>::operator bool() const {
  if constexpr (std::is_same_v<T, bool>) {
    return x() and y();
  } else {
    return (norm(*this) > zero<T>);
  }
}

template <typename T>
inline constexpr T &Vector<2, T>::operator[](UInt32 pos) {
  return m_data[pos];
}

template <typename T>
inline constexpr const T &Vector<2, T>::operator[](UInt32 pos) const {
  return m_data[pos];
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
  return va.m_data == vb.m_data;
}

template <typename U>
inline constexpr bool operator!=(const Vector<2, U> &va,
                                 const Vector<2, U> &vb) {
  return not(va == vb);
}

// Output stream operator
template <typename T>
inline constexpr std::ostream &operator<<(std::ostream &os,
                                          const Vector<2, T> &v) {
  return os << "Vector2<" << typeid(T).name() << ">{" << v.x() << ", " << v.y()
            << "}";
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