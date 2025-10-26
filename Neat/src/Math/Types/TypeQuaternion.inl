#include "TypeQuaternion.hpp"

#include "Math/Trigonometric.hpp"

namespace Neat {
// Quaternion/Matrix conversion
template <typename T>
Matrix<3, 3, T> Matrix3Cast(const Quaternion<T> &q) {
  Matrix<3, 3, T> result{};
  T qxx = q.x() * q.x();
  T qyy = q.y() * q.y();
  T qzz = q.z() * q.z();
  T qxz = q.x() * q.z();
  T qxy = q.x() * q.y();
  T qyz = q.y() * q.z();
  T qwx = q.w() * q.x();
  T qwy = q.w() * q.y();
  T qwz = q.w() * q.z();

  result(0, 0) = One<T> - Two<T> * (qyy + qzz);
  result(1, 0) = Two<T> * (qxy + qwz);
  result(2, 0) = Two<T> * (qxz - qwy);
  result(0, 1) = Two<T> * (qxy - qwz);
  result(1, 1) = One<T> - Two<T> * (qxx + qzz);
  result(2, 1) = Two<T> * (qyz + qwx);
  result(0, 2) = Two<T> * (qxz + qwy);
  result(1, 2) = Two<T> * (qyz - qwx);
  result(2, 2) = One<T> - Two<T> * (qxx + qyy);

  return result;
}

template <typename T>
Matrix<4, 4, T> Matrix4Cast(const Quaternion<T> &q) {
  return Matrix<4, 4, T>{Matrix3Cast(q)};
}

template <typename T>
Quaternion<T> QuaternionCast(const Matrix<3, 3, T> &m) {
  T four_x_squared_minus1 = m(0, 0) - m(1, 1) - m(2, 2);
  T four_y_squared_minus1 = m(1, 1) - m(0, 0) - m(2, 2);
  T four_z_squared_minus1 = m(2, 2) - m(0, 0) - m(1, 1);
  T four_w_squared_minus1 = m(0, 0) + m(1, 1) + m(2, 2);

  int biggest_index = 0;
  T four_biggest_squared_minus1 = four_w_squared_minus1;
  if (four_x_squared_minus1 > four_biggest_squared_minus1) {
    four_biggest_squared_minus1 = four_x_squared_minus1;
    biggest_index = 1;
  }
  if (four_y_squared_minus1 > four_biggest_squared_minus1) {
    four_biggest_squared_minus1 = four_y_squared_minus1;
    biggest_index = 2;
  }
  if (four_z_squared_minus1 > four_biggest_squared_minus1) {
    four_biggest_squared_minus1 = four_z_squared_minus1;
    biggest_index = 3;
  }

  T biggest_value = sqrt(four_biggest_squared_minus1 + One<T>) * OneHalf<T>;
  T factor = OneForth<T> / biggest_value;

  switch (biggest_index) {
    case 0:
      return Quaternion<T>{biggest_value, (m(1, 2) - m(2, 1)) * factor,
                           (m(2, 0) - m(0, 2)) * factor,
                           (m(0, 1) - m(1, 0)) * factor};

    case 1:
      return Quaternion<T>{(m(1, 2) - m(2, 1)) * factor, biggest_value,
                           (m(0, 1) + m(1, 0)) * factor,
                           (m(2, 0) + m(0, 2)) * factor};

    case 2:
      return Quaternion<T>{(m(2, 0) - m(0, 2)) * factor,
                           (m(0, 1) + m(1, 0)) * factor, biggest_value,
                           (m(1, 2) + m(2, 1)) * factor};

    case 3:
      return Quaternion<T>{(m(0, 1) - m(1, 0)) * factor,
                           (m(2, 0) + m(0, 2)) * factor,
                           (m(1, 2) + m(2, 1)) * factor, biggest_value};

    default:
      return Quaternion<T>{};
  }
}

template <typename T>
Quaternion<T> QuaternionCast(const Matrix<4, 4, T> &m) {
  return QuaternionCast(Matrix<3, 3, T>{m});
}

// Default constructor
template <typename T>
inline constexpr Quaternion<T>::Quaternion()
    : elements{One<T>, Zero<T>, Zero<T>, Zero<T>} {}

// Basic constructors
template <typename T>
inline constexpr Quaternion<T>::Quaternion(T s, const Vector<3, T> &v)
    : elements{s, v.x(), v.y(), v.z()} {}

template <typename T>
inline constexpr Quaternion<T>::Quaternion(T w, T x, T y, T z)
    : elements{w, x, y, z} {}

// Copy Constructor
template <typename T>
inline constexpr Quaternion<T>::Quaternion(const Quaternion<T> &q)
    : elements{q.elements} {}

// Conversion constructors
template <typename T>
template <typename U>
inline constexpr Quaternion<T>::Quaternion(const Quaternion<U> &q)
    : elements{static_cast<T>(q.w()), static_cast<T>(q.x()),
               static_cast<T>(q.y()), static_cast<T>(q.z())} {}

// Matrix constructor
template <typename T>
inline constexpr Quaternion<T>::Quaternion(const Matrix<3, 3, T> &rotation) {
  *this = QuaternionCast(rotation);
}

template <typename T>
inline constexpr Quaternion<T>::Quaternion(const Matrix<4, 4, T> &rotation) {
  *this = QuaternionCast(rotation);
}

// Static factory constructors
template <typename T>
inline constexpr Quaternion<T> Quaternion<T>::fromAngleAxis(
    T angleRadians, const Vector<3, T> &axis) {
  return Quaternion<T>{cos(angleRadians / 2), sin(angleRadians / 2) * axis};
}

template <typename T>
inline constexpr Quaternion<T> Quaternion<T>::fromEulerAngles(T pitch, T yaw,
                                                              T roll) {
  return fromEulerAngles(Vector<3, T>{pitch, yaw, roll});
}

template <typename T>
inline constexpr Quaternion<T> Quaternion<T>::fromEulerAngles(
    const Vector<3, T> &pitchYawRoll) {
  Vector<3, T> c{cos(pitchYawRoll * OneHalf<T>)};
  Vector<3, T> s{sin(pitchYawRoll * OneHalf<T>)};

  return Quaternion<T>{c.x() * c.y() * c.z() + s.x() * s.y() * s.z(),
                       s.x() * c.y() * c.z() - c.x() * s.y() * s.z(),
                       c.x() * s.y() * c.z() + s.x() * c.y() * s.z(),
                       c.x() * c.y() * s.z() - s.x() * s.y() * c.z()};
}

// Member converters
template <typename T>
inline constexpr Matrix<3, 3, T> Quaternion<T>::toMatrix3() const {
  return Matrix3Cast(*this);
}

template <typename T>
inline constexpr Matrix<4, 4, T> Quaternion<T>::toMatrix4() const {
  return Matrix4Cast(*this);
}

// Assignment operators
template <typename T>
template <typename U>
inline constexpr Quaternion<T> &Quaternion<T>::operator=(
    const Quaternion<U> &q) {
  elements = q.elements;

  return *this;
}

// Compound assignment operators
template <typename T>
template <typename U>
inline constexpr Quaternion<T> &Quaternion<T>::operator+=(
    const Quaternion<U> &q) {
  elements = {static_cast<T>(q.w()), static_cast<T>(q.x()),
              static_cast<T>(q.y()), static_cast<T>(q.z())};

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Quaternion<T> &Quaternion<T>::operator-=(
    const Quaternion<U> &q) {
  elements[0] -= static_cast<T>(q.w());
  elements[1] -= static_cast<T>(q.x());
  elements[2] -= static_cast<T>(q.y());
  elements[3] -= static_cast<T>(q.z());

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Quaternion<T> &Quaternion<T>::operator*=(
    const Quaternion<U> &q) {
  elements[0] = elements[0] * q.w() - elements[1] * q.x() -
                elements[2] * q.y() - elements[3] * q.z();
  elements[1] = elements[0] * q.x() + elements[1] * q.w() +
                elements[2] * q.z() - elements[3] * q.y();
  elements[2] = elements[0] * q.y() + elements[1] * q.x() +
                elements[3] * q.x() - elements[2] * q.z();
  elements[3] = elements[0] * q.z() + elements[1] * q.y() +
                elements[2] * q.x() - elements[3] * q.w();

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Quaternion<T> &Quaternion<T>::operator*=(U scalar) {
  elements[0] *= static_cast<T>(scalar);
  elements[1] *= static_cast<T>(scalar);
  elements[2] *= static_cast<T>(scalar);
  elements[3] *= static_cast<T>(scalar);

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Quaternion<T> &Quaternion<T>::operator/=(U scalar) {
  elements[0] /= static_cast<T>(scalar);
  elements[1] /= static_cast<T>(scalar);
  elements[2] /= static_cast<T>(scalar);
  elements[3] /= static_cast<T>(scalar);

  return *this;
}

// Explicit conversion operators
template <typename T>
inline Quaternion<T>::operator Matrix<3, 3, T>() const {
  return Matrix3Cast(*this);
}

template <typename T>
inline Quaternion<T>::operator Matrix<4, 4, T>() const {
  return Matrix4Cast(*this);
}

// Elements accessing
template <typename T>
inline constexpr T &Quaternion<T>::operator[](UInt32 pos) {
  return elements[pos];
}

template <typename T>
inline constexpr const T &Quaternion<T>::operator[](UInt32 pos) const {
  return elements[pos];
}

// Non member operators
template <typename T>
inline constexpr Quaternion<T> operator+(const Quaternion<T> &qa,
                                         const Quaternion<T> &qb) {
  return Quaternion<T>{qa} += qb;
}

template <typename T>
inline constexpr Quaternion<T> operator-(const Quaternion<T> &q) {
  return Quaternion<T>{-q.w(), -q.x(), -q.y(), -q.z()};
}

template <typename T>
inline constexpr Quaternion<T> operator-(const Quaternion<T> &qa,
                                         const Quaternion<T> &qb) {
  return Quaternion<T>{qa} -= qb;
}

template <typename T>
inline constexpr Quaternion<T> operator*(const Quaternion<T> &qa,
                                         const Quaternion<T> &qb) {
  return Quaternion<T>{qa} *= qb;
}

template <typename T>
inline constexpr Vector<3, T> operator*(const Quaternion<T> &q,
                                        const Vector<3, T> &v) {
  // Quaternion rotation optimization
  // Considering that converting v to a quaternion results in a expensive
  // multiplication with a quaternion with w component equals to 0
  Vector<3, T> uv(cross(q.v(), v));
  Vector<3, T> uuv(cross(q.v(), uv));

  return v + Two<T> * (uv * q.w() + uuv);
}

template <typename T>
inline constexpr Vector<3, T> operator*(const Vector<3, T> &v,
                                        const Quaternion<T> &q) {
  return inverse(q) * v;
}

template <typename T>
inline constexpr Vector<4, T> operator*(const Quaternion<T> &q,
                                        const Vector<4, T> &v) {
  return Vector<4, T>{q * Vector<3, T>(v), v.w};
}

template <typename T>
inline constexpr Vector<4, T> operator*(const Vector<4, T> &v,
                                        const Quaternion<T> &q) {
  return inverse(q) * v;
}

template <typename T>
inline constexpr Quaternion<T> operator*(const Quaternion<T> &q,
                                         const T &scalar) {
  return Quaternion<T>{q} *= scalar;
}

template <typename T>
inline constexpr Quaternion<T> operator*(T const &scalar,
                                         const Quaternion<T> &q) {
  return Quaternion<T>{q} *= scalar;
}

template <typename T>
inline constexpr Quaternion<T> operator/(const Quaternion<T> &q,
                                         const T &scalar) {
  return Quaternion<T>{q} /= scalar;
}

// Relational operators
template <typename T>
inline constexpr bool operator==(const Quaternion<T> &qa,
                                 const Quaternion<T> &qb) {
  return qa.elements == qb.elements;
}

template <typename T>
inline constexpr bool operator!=(const Quaternion<T> &qa,
                                 const Quaternion<T> &qb) {
  return not(qa == qb);
}

// Quaternion operations
template <typename T>
inline constexpr T dot(const Quaternion<T> &qa, const Quaternion<T> &qb) {
  return qa.w * qb.w + qa.x * qb.x + qa.y + qb.y + qa.z * qb.z;
}

template <typename T>
inline constexpr Quaternion<T> cross(const Quaternion<T> &qa,
                                     const Quaternion<T> &qb) {
  return qa * qb;
}

template <typename T>
inline constexpr T norm(const Quaternion<T> &q) {
  return sqrt(dot(q, q));
}

template <typename T>
inline constexpr Quaternion<T> normalize(const Quaternion<T> &q) {
  T one_over_norm = One<T> / norm(q);
  return q * one_over_norm;
}

template <typename T>
inline constexpr Quaternion<T> conjugate(const Quaternion<T> &q) {
  return Quaternion<T>(q.w(), -q.v());
}

template <typename T>
inline constexpr Quaternion<T> inverse(const Quaternion<T> &q) {
  return conjugate(q) / dot(q, q);
}

template <typename T>
inline constexpr Vector<3, T> rotate(const Quaternion<T> &q,
                                     const Vector<3, T> &v) {
  return q * v;
}

template <typename T>
inline constexpr Vector<4, T> rotate(const Quaternion<T> &q,
                                     const Vector<4, T> &v) {
  return q * v;
}
}  // namespace Neat