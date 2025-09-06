#include "Neat/Math/Exponential.hpp"

namespace Neat {
// Default constructor
template <typename T>
inline constexpr Vector<1, T>::Vector() : m_data{zero<T>} {}

// Basic Constructors
template <typename T>
inline constexpr Vector<1, T>::Vector(const T &scalar) : m_data{scalar} {}

template <typename T>
inline constexpr Vector<1, T>::Vector(const std::array<T, 1> &data)
    : m_data{data} {}

// Copy Constructor
template <typename T>
inline constexpr Vector<1, T>::Vector(const Vector<1, T> &v)
    : m_data{v.m_data} {}

// Conversion constructors
template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const Vector<1, U> &v)
    : m_data{static_cast<T>(v.x())} {}

template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const Vector<4, U> &v)
    : m_data{static_cast<T>(v.x())} {}

template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const Vector<3, U> &v)
    : m_data{static_cast<T>(v.x())} {}

template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const Vector<2, U> &v)
    : m_data{static_cast<T>(v.x())} {}

template <typename T>
template <typename U>
inline constexpr Vector<1, T>::Vector(const U &x) : m_data{static_cast<T>(x)} {}

// Assignment operators
template <typename T>
inline constexpr Vector<1, T> &Vector<1, T>::operator=(const T &scalar) {
  m_data[0] = scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator=(
    const Vector<1, U> &other) {
  x() = other.x();

  return *this;
}

// Compound assignment operators
template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator+=(const Vector<1, U> &v) {
  x() += v.x();

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator-=(const Vector<1, U> &v) {
  x() -= v.x();

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator*=(const Vector<1, U> &v) {
  x() *= v.x();

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator*=(const U &scalar) {
  x() *= scalar;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Vector<1, T> &Vector<1, T>::operator/=(const U &scalar) {
  x() /= scalar;

  return *this;
}

template <typename T>
inline constexpr Vector<1, T>::operator bool() const {
  if constexpr (std::is_same_v<T, bool>) {
    return x();
  } else {
    return (std::fabs(x()) > zero<T>);
  }
}

template <typename T>
inline constexpr T &Vector<1, T>::operator[](UInt32 pos) {
  return m_data[pos];
}

template <typename T>
inline constexpr const T &Vector<1, T>::operator[](UInt32 pos) const {
  return m_data[pos];
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
  return Vector<1, T>(v) /= scalar;
}

// Relational operators
template <typename U>
inline constexpr bool operator==(const Vector<1, U> &va,
                                 const Vector<1, U> &vb) {
  return va.data() == vb.data();
}

template <typename U>
inline constexpr bool operator!=(const Vector<1, U> &va,
                                 const Vector<1, U> &vb) {
  return not(va == vb);
}

// Output stream operator
template <typename T>
inline constexpr std::ostream &operator<<(std::ostream &os,
                                          const Vector<1, T> &v) {
  return os << "Vector1<" << typeid(T).name() << ">{" << v.x() << "}";
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
  T one_over_norm = one<T> / norm(v);

  return one_over_norm * v;
}
}  // namespace Neat