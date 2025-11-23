#include <cmath>

#include "Constants.hpp"
#include "Trigonometric.hpp"
#include "Transform.hpp"

namespace Neat {
// Vector
template <typename T>
inline Matrix<4, 4, T> translate(const Vector<3, T> &v) {
  return Matrix<4, 4, T>(One<T>, Zero<T>, Zero<T>, v.x(), Zero<T>, One<T>,
                         Zero<T>, v.y(), Zero<T>, Zero<T>, One<T>, v.z(),
                         Zero<T>, Zero<T>, Zero<T>, One<T>);
}

template <typename T>
inline Matrix<4, 4, T> translate(const Matrix<4, 4, T> &m,
                                 const Vector<3, T> &v) {
  Matrix<4, 4, T> result{m};
  result(0, 3) = v.x() * m(0, 0) + v.y() * m(0, 1) + v.z() * m(0, 2) + m(0, 3);
  result(1, 3) = v.x() * m(1, 0) + v.y() * m(1, 1) + v.z() * m(1, 2) + m(1, 3);
  result(2, 3) = v.x() * m(2, 0) + v.y() * m(2, 1) + v.z() * m(2, 2) + m(2, 3);
  result(3, 3) = v.x() * m(3, 0) + v.y() * m(3, 1) + v.z() * m(3, 2) + m(3, 3);

  return result;
}

template <typename T>
inline Matrix<4, 4, T> rotate(const T &angleRadians,
                              const Vector<3, T> &rotationAxis) {
  T cosine = cos(angleRadians);
  T sine = sin(angleRadians);
  Vector<3, T> axis{normalize(rotationAxis)};

  T oneMinusCosTimesX = (One<T> - cosine) * axis.x();
  T oneMinusCosTimesY = (One<T> - cosine) * axis.y();
  T oneMinusCosTimesZ = (One<T> - cosine) * axis.z();

  T x2c = oneMinusCosTimesX * axis.x();
  T xyc = oneMinusCosTimesX * axis.y();
  T xzc = oneMinusCosTimesX * axis.z();
  T y2c = oneMinusCosTimesY * axis.y();
  T yzc = oneMinusCosTimesY * axis.z();
  T z2c = oneMinusCosTimesZ * axis.z();

  T r00 = x2c + cosine;
  T r10 = xyc + axis.z() * sine;
  T r20 = xzc - axis.y() * sine;
  T r01 = xyc - axis.z() * sine;
  T r11 = y2c + cosine;
  T r21 = yzc + axis.x() * sine;
  T r02 = xzc + axis.y() * sine;
  T r12 = yzc - axis.x() * sine;
  T r22 = z2c + cosine;

  return Matrix<4, 4, T>{r00,     r01,     r02,     Zero<T>, r10, r11,
                         r12,     Zero<T>, r20,     r21,     r22, Zero<T>,
                         Zero<T>, Zero<T>, Zero<T>, One<T>};
}

template <typename T>
inline Matrix<4, 4, T> rotate(const Matrix<4, 4, T> &m, const T &angleRadians,
                              const Vector<3, T> &rotationAxis) {
  T cosine = cos(angleRadians);
  T sine = sin(angleRadians);
  Vector<3, T> axis{normalize(rotationAxis)};

  T oneMinusCosTimesX = (One<T> - cosine) * axis.x();
  T oneMinusCosTimesY = (One<T> - cosine) * axis.y();
  T oneMinusCosTimesZ = (One<T> - cosine) * axis.z();

  T x2c = oneMinusCosTimesX * axis.x();
  T xyc = oneMinusCosTimesX * axis.y();
  T xzc = oneMinusCosTimesX * axis.z();
  T y2c = oneMinusCosTimesY * axis.y();
  T yzc = oneMinusCosTimesY * axis.z();
  T z2c = oneMinusCosTimesZ * axis.z();

  T r00 = x2c + cosine;
  T r10 = xyc + axis.z() * sine;
  T r20 = xzc - axis.y() * sine;
  T r01 = xyc - axis.z() * sine;
  T r11 = y2c + cosine;
  T r21 = yzc + axis.x() * sine;
  T r02 = xzc + axis.y() * sine;
  T r12 = yzc - axis.x() * sine;
  T r22 = z2c + cosine;

  return Matrix<4, 4, T>{r00 * m(0, 0) + r01 * m(1, 0) + r02 * m(2, 0),
                         r00 * m(0, 1) + r01 * m(1, 1) + r02 * m(2, 1),
                         r00 * m(0, 2) + r01 * m(1, 2) + r02 * m(2, 2),
                         r00 * m(0, 3) + r01 * m(1, 3) + r02 * m(2, 3),
                         r10 * m(0, 0) + r11 * m(1, 0) + r12 * m(2, 0),
                         r10 * m(0, 1) + r11 * m(1, 1) + r12 * m(2, 1),
                         r10 * m(0, 2) + r11 * m(1, 2) + r12 * m(2, 2),
                         r10 * m(0, 3) + r11 * m(1, 3) + r12 * m(2, 3),
                         r20 * m(0, 0) + r21 * m(1, 0) + r22 * m(2, 0),
                         r20 * m(0, 1) + r21 * m(1, 1) + r22 * m(2, 1),
                         r20 * m(0, 2) + r21 * m(1, 2) + r22 * m(2, 2),
                         r20 * m(0, 3) + r21 * m(1, 3) + r22 * m(2, 3),
                         Zero<T>,
                         Zero<T>,
                         Zero<T>,
                         m(3, 3)};
}

template <typename T>
inline Matrix<4, 4, T> rotateX(const T &angleRadians) {
  T cosX = cos(angleRadians);
  T sinX = sin(angleRadians);

  return Matrix<4, 4, T>{One<T>,  Zero<T>, Zero<T>, Zero<T>, Zero<T>, cosX,
                         -sinX,   Zero<T>, Zero<T>, sinX,    cosX,    Zero<T>,
                         Zero<T>, Zero<T>, Zero<T>, One<T>};
}

template <typename T>
inline Matrix<4, 4, T> rotateY(const T &angleRadians) {
  T cosY = cos(angleRadians);
  T sinY = sin(angleRadians);

  return Matrix<4, 4, T>{cosY,    Zero<T>, sinY,    Zero<T>, Zero<T>, One<T>,
                         Zero<T>, Zero<T>, -sinY,   Zero<T>, cosY,    Zero<T>,
                         Zero<T>, Zero<T>, Zero<T>, One<T>};
}

template <typename T>
inline Matrix<4, 4, T> rotateZ(const T &angleRadians) {
  T cosZ = cos(angleRadians);
  T sinZ = sin(angleRadians);

  return Matrix<4, 4, T>{cosZ,    -sinZ,   Zero<T>, Zero<T>, sinZ,   cosZ,
                         Zero<T>, Zero<T>, Zero<T>, Zero<T>, One<T>, Zero<T>,
                         Zero<T>, Zero<T>, Zero<T>, One<T>};
}

template <typename T>
inline Matrix<4, 4, T> scale(const Vector<3, T> &v) {
  return Matrix<4, 4, T>{v.x(),   Zero<T>, Zero<T>, Zero<T>, Zero<T>, v.y(),
                         Zero<T>, Zero<T>, Zero<T>, Zero<T>, v.z(),   Zero<T>,
                         Zero<T>, Zero<T>, Zero<T>, One<T>};
}

template <typename T>
inline Matrix<4, 4, T> scale(const Matrix<4, 4, T> &m, const Vector<3, T> &v) {
  return Matrix<4, 4, T>{
      m(0, 0) * v.x(), m(0, 1) * v.y(), m(0, 2) * v.z(), m(0, 3),
      m(1, 0) * v.x(), m(1, 1) * v.y(), m(1, 2) * v.z(), m(1, 3),
      m(2, 0) * v.x(), m(2, 1) * v.y(), m(2, 2) * v.z(), m(2, 3),
      m(3, 0) * v.x(), m(3, 1) * v.y(), m(3, 2) * v.z(), m(3, 3)};
}

// Quaternion
template <typename T>
inline Quaternion<T> rotate(const Quaternion<T> &q, const T &angleRadians,
                            const Vector<3, T> &rotationAxis) {
  return q *
         Quaternion<T>::fromAngleAxis(angleRadians, normalize(rotationAxis));
}
}  // namespace Neat