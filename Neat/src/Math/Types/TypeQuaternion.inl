#include "Math/Trigonometric.hpp"
#include "Math/Constants.hpp"

#include "Core/Assert.hpp"

namespace Neat {
// Quaternion/Matrix conversion
template <typename T>
Matrix<3, 3, T> matrix3Cast(const Quaternion<T> &q) {
  Quaternion<T> normalizedQ = normalize(q);
  Matrix<3, 3, T> result{};
  T qxx = normalizedQ.x() * normalizedQ.x();
  T qyy = normalizedQ.y() * normalizedQ.y();
  T qzz = normalizedQ.z() * normalizedQ.z();
  T qxz = normalizedQ.x() * normalizedQ.z();
  T qxy = normalizedQ.x() * normalizedQ.y();
  T qyz = normalizedQ.y() * normalizedQ.z();
  T qwx = normalizedQ.w() * normalizedQ.x();
  T qwy = normalizedQ.w() * normalizedQ.y();
  T qwz = normalizedQ.w() * normalizedQ.z();

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
Matrix<4, 4, T> matrix4Cast(const Quaternion<T> &q) {
  return Matrix<4, 4, T>{matrix3Cast(q)};
}

template <typename T>
Quaternion<T> quaternionCast(const Matrix<3, 3, T> &m) {
  T fourXSquaredMinus1 = m(0, 0) - m(1, 1) - m(2, 2);
  T fourYSquaredMinus1 = m(1, 1) - m(0, 0) - m(2, 2);
  T fourZSquaredMinus1 = m(2, 2) - m(0, 0) - m(1, 1);
  T fourWSquaredMinus1 = m(0, 0) + m(1, 1) + m(2, 2);

  int biggestIndex = 0;
  T fourBiggerSquaredMinus1 = fourWSquaredMinus1;
  if (fourXSquaredMinus1 > fourBiggerSquaredMinus1) {
    fourBiggerSquaredMinus1 = fourXSquaredMinus1;
    biggestIndex = 1;
  }
  if (fourYSquaredMinus1 > fourBiggerSquaredMinus1) {
    fourBiggerSquaredMinus1 = fourYSquaredMinus1;
    biggestIndex = 2;
  }
  if (fourZSquaredMinus1 > fourBiggerSquaredMinus1) {
    fourBiggerSquaredMinus1 = fourZSquaredMinus1;
    biggestIndex = 3;
  }

  T biggestValue = sqrt(fourBiggerSquaredMinus1 + One<T>) * OneHalf<T>;
  T factor = OneForth<T> / biggestValue;

  switch (biggestIndex) {
    case 0:
      return Quaternion<T>{biggestValue, (m(2, 1) - m(1, 2)) * factor,
                           (m(0, 2) - m(2, 0)) * factor,
                           (m(1, 0) - m(0, 1)) * factor};

    case 1:
      return Quaternion<T>{(m(2, 1) - m(1, 2)) * factor, biggestValue,
                           (m(1, 0) + m(0, 1)) * factor,
                           (m(0, 2) + m(2, 0)) * factor};

    case 2:
      return Quaternion<T>{(m(0, 2) - m(2, 0)) * factor,
                           (m(1, 0) + m(0, 1)) * factor, biggestValue,
                           (m(2, 1) + m(1, 2)) * factor};

    case 3:
      return Quaternion<T>{(m(1, 0) - m(0, 1)) * factor,
                           (m(0, 2) + m(2, 0)) * factor,
                           (m(2, 1) + m(1, 2)) * factor, biggestValue};

    default:
      NT_CORE_ASSERT(false, "Unreachable code reached in quaternionCast.");
      return Quaternion<T>{};
  }
}

template <typename T>
Quaternion<T> quaternionCast(const Matrix<4, 4, T> &m) {
  return quaternionCast(Matrix<3, 3, T>{m});
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
  *this = quaternionCast(rotation);
}

template <typename T>
inline constexpr Quaternion<T>::Quaternion(const Matrix<4, 4, T> &rotation) {
  *this = quaternionCast(rotation);
}

// Static factory constructors
template <typename T>
inline constexpr Quaternion<T> Quaternion<T>::fromAngleAxis(
    T angleRadians, const Vector<3, T> &axis) {
  return Quaternion<T>{cos(angleRadians / 2), sin(angleRadians / 2) * axis};
}

template <typename T>
inline constexpr Quaternion<T> Quaternion<T>::fromEulerAnglesXYZ(T pitch, T yaw,
                                                                 T roll) {
  return fromEulerAnglesXYZ(Vector<3, T>{pitch, yaw, roll});
}

template <typename T>
inline constexpr Quaternion<T> Quaternion<T>::fromEulerAnglesXYZ(
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
  return matrix3Cast(*this);
}

template <typename T>
inline constexpr Matrix<4, 4, T> Quaternion<T>::toMatrix4() const {
  return matrix4Cast(*this);
}

// Assignment operators
template <typename T>
template <typename U>
inline constexpr Quaternion<T> &Quaternion<T>::operator=(
    const Quaternion<U> &q) {
  w() = static_cast<T>(q.w());
  x() = static_cast<T>(q.x());
  y() = static_cast<T>(q.y());
  z() = static_cast<T>(q.z());

  return *this;
}

// Compound assignment operators
template <typename T>
template <typename U>
inline constexpr Quaternion<T> &Quaternion<T>::operator+=(
    const Quaternion<U> &q) {
  w() += static_cast<T>(q.w());
  x() += static_cast<T>(q.x());
  y() += static_cast<T>(q.y());
  z() += static_cast<T>(q.z());

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Quaternion<T> &Quaternion<T>::operator-=(
    const Quaternion<U> &q) {
  w() -= static_cast<T>(q.w());
  x() -= static_cast<T>(q.x());
  y() -= static_cast<T>(q.y());
  z() -= static_cast<T>(q.z());

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Quaternion<T> &Quaternion<T>::operator*=(
    const Quaternion<U> &q) {
  T qw = w() * static_cast<T>(q.w()) - x() * static_cast<T>(q.x()) -
         y() * static_cast<T>(q.y()) - z() * static_cast<T>(q.z());
  T qx = w() * static_cast<T>(q.x()) + x() * static_cast<T>(q.w()) +
         y() * static_cast<T>(q.z()) - z() * static_cast<T>(q.y());
  T qy = w() * static_cast<T>(q.y()) - x() * static_cast<T>(q.z()) +
         y() * static_cast<T>(q.w()) + z() * static_cast<T>(q.x());
  T qz = w() * static_cast<T>(q.z()) + x() * static_cast<T>(q.y()) -
         y() * static_cast<T>(q.x()) + z() * static_cast<T>(q.w());
  w() = qw;
  x() = qx;
  y() = qy;
  z() = qz;

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Quaternion<T> &Quaternion<T>::operator*=(U scalar) {
  w() *= static_cast<T>(scalar);
  x() *= static_cast<T>(scalar);
  y() *= static_cast<T>(scalar);
  z() *= static_cast<T>(scalar);

  return *this;
}

template <typename T>
template <typename U>
inline constexpr Quaternion<T> &Quaternion<T>::operator/=(U scalar) {
  w() /= static_cast<T>(scalar);
  x() /= static_cast<T>(scalar);
  y() /= static_cast<T>(scalar);
  z() /= static_cast<T>(scalar);

  return *this;
}

// Explicit conversion operators
template <typename T>
inline Quaternion<T>::operator Matrix<3, 3, T>() const {
  return matrix3Cast(*this);
}

template <typename T>
inline Quaternion<T>::operator Matrix<4, 4, T>() const {
  return matrix4Cast(*this);
}

// Elements accessing
template <typename T>
inline constexpr T &Quaternion<T>::operator[](UInt32 pos) {
  NT_CORE_ASSERT(pos < N, "Quaternion index out of bounds");

  return elements[pos];
}

template <typename T>
inline constexpr const T &Quaternion<T>::operator[](UInt32 pos) const {
  NT_CORE_ASSERT(pos < N, "Quaternion index out of bounds");

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
  return Vector<4, T>{q * Vector<3, T>(v), v.w()};
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
  NT_CORE_ASSERT(scalar != Zero<T>,
                 "Division by zero in Quaternion scalar division.");

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
  return qa.w() * qb.w() + qa.x() * qb.x() + qa.y() * qb.y() + qa.z() * qb.z();
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
  T oneOverNorm = One<T> / norm(q);
  return q * oneOverNorm;
}

template <typename T>
inline constexpr Quaternion<T> conjugate(const Quaternion<T> &q) {
  return Quaternion<T>(q.w(), -q.v());
}

template <typename T>
inline constexpr Quaternion<T> inverse(const Quaternion<T> &q) {
  T dotProduct = dot(q, q);
  if (dotProduct == Zero<T>) {
    NT_CORE_ASSERT(false, "Cannot invert a quaternion with zero norm.");
    return Quaternion<T>{};
  }

  return conjugate(q) / dotProduct;
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