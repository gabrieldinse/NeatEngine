#include "Constants.hpp"
#include "Trigonometric.hpp"

namespace Neat {
template <typename T>
inline Matrix<4, 4, T> eulerAnglesXYZ(const T &angle1, const T &angle2,
                                      const T &angle3) {
  T c1 = cos(-angle1);
  T c2 = cos(-angle2);
  T c3 = cos(-angle3);
  T s1 = sin(-angle1);
  T s2 = sin(-angle2);
  T s3 = sin(-angle3);

  Matrix<4, 4, T> result{};
  result(0, 0) = c2 * c3;
  result(1, 0) = -c1 * s3 + s1 * s2 * c3;
  result(2, 0) = s1 * s3 + c1 * s2 * c3;
  result(0, 1) = c2 * s3;
  result(1, 1) = c1 * c3 + s1 * s2 * s3;
  result(2, 1) = -s1 * c3 + c1 * s2 * s3;
  result(0, 2) = -s2;
  result(1, 2) = s1 * c2;
  result(2, 2) = c1 * c2;

  return result;
}

template <typename T>
inline Matrix<4, 4, T> eulerAnglesYXZ(const T &yaw, const T &pitch,
                                      const T &roll) {
  T cy = cos(yaw);
  T sy = sin(yaw);
  T cp = cos(pitch);
  T sp = sin(pitch);
  T cr = cos(roll);
  T sr = sin(roll);

  Matrix<4, 4, T> result{};
  result(0, 0) = cy * cr + sy * sp * sr;
  result(1, 0) = sr * cp;
  result(2, 0) = -sy * cr + cy * sp * sr;
  result(0, 1) = -cy * sr + sy * sp * cr;
  result(1, 1) = cr * cp;
  result(2, 1) = sr * sy + cy * sp * cr;
  result(0, 2) = sy * cp;
  result(1, 2) = -sp;
  result(2, 2) = cy * cp;

  return result;
}

template <typename T>
inline Matrix<4, 4, T> eulerAnglesXZX(const T &angle1, const T &angle2,
                                      const T &angle3) {
  T c1 = cos(angle1);
  T s1 = sin(angle1);
  T c2 = cos(angle2);
  T s2 = sin(angle2);
  T c3 = cos(angle3);
  T s3 = sin(angle3);

  Matrix<4, 4, T> result{};
  result(0, 0) = c2;
  result(1, 0) = c1 * s2;
  result(2, 0) = s1 * s2;
  result(0, 1) = -c3 * s2;
  result(1, 1) = c1 * c2 * c3 - s1 * s3;
  result(2, 1) = c1 * s3 + c2 * c3 * s1;
  result(0, 2) = s2 * s3;
  result(1, 2) = -c3 * s1 - c1 * c2 * s3;
  result(2, 2) = c1 * c3 - c2 * s1 * s3;

  return result;
}

template <typename T>
inline Matrix<4, 4, T> eulerAnglesXYX(const T &angle1, const T &angle2,
                                      const T &angle3) {
  T c1 = cos(angle1);
  T s1 = sin(angle1);
  T c2 = cos(angle2);
  T s2 = sin(angle2);
  T c3 = cos(angle3);
  T s3 = sin(angle3);

  Matrix<4, 4, T> result{};
  result(0, 0) = c2;
  result(1, 0) = s1 * s2;
  result(2, 0) = -c1 * s2;
  result(0, 1) = s2 * s3;
  result(1, 1) = c1 * c3 - c2 * s1 * s3;
  result(2, 1) = c3 * s1 + c1 * c2 * s3;
  result(0, 2) = c3 * s2;
  result(1, 2) = -c1 * s3 - c2 * c3 * s1;
  result(2, 2) = c1 * c2 * c3 - s1 * s3;

  return result;
}

template <typename T>
inline Matrix<4, 4, T> eulerAnglesYXY(const T &angle1, const T &angle2,
                                      const T &angle3) {
  T c1 = cos(angle1);
  T s1 = sin(angle1);
  T c2 = cos(angle2);
  T s2 = sin(angle2);
  T c3 = cos(angle3);
  T s3 = sin(angle3);

  Matrix<4, 4, T> result{};
  result(0, 0) = c1 * c3 - c2 * s1 * s3;
  result(1, 0) = s2 * s3;
  result(2, 0) = -c3 * s1 - c1 * c2 * s3;
  result(0, 1) = s1 * s2;
  result(1, 1) = c2;
  result(2, 1) = c1 * s2;
  result(0, 2) = c1 * s3 + c2 * c3 * s1;
  result(1, 2) = -c3 * s2;
  result(2, 2) = c1 * c2 * c3 - s1 * s3;

  return result;
}

template <typename T>
inline Matrix<4, 4, T> eulerAnglesYZY(const T &angle1, const T &angle2,
                                      const T &angle3) {
  T c1 = cos(angle1);
  T s1 = sin(angle1);
  T c2 = cos(angle2);
  T s2 = sin(angle2);
  T c3 = cos(angle3);
  T s3 = sin(angle3);

  Matrix<4, 4, T> result{};
  result(0, 0) = c1 * c2 * c3 - s1 * s3;
  result(1, 0) = c3 * s2;
  result(2, 0) = -c1 * s3 - c2 * c3 * s1;
  result(0, 1) = -c1 * s2;
  result(1, 1) = c2;
  result(2, 1) = s1 * s2;
  result(0, 2) = c3 * s1 + c1 * c2 * s3;
  result(1, 2) = s2 * s3;
  result(2, 2) = c1 * c3 - c2 * s1 * s3;

  return result;
}

template <typename T>
inline Matrix<4, 4, T> eulerAnglesZYZ(const T &angle1, const T &angle2,
                                      const T &angle3) {
  T c1 = cos(angle1);
  T s1 = sin(angle1);
  T c2 = cos(angle2);
  T s2 = sin(angle2);
  T c3 = cos(angle3);
  T s3 = sin(angle3);

  Matrix<4, 4, T> result{};
  result(0, 0) = c1 * c2 * c3 - s1 * s3;
  result(1, 0) = c1 * s3 + c2 * c3 * s1;
  result(2, 0) = -c3 * s2;
  result(0, 1) = -c3 * s1 - c1 * c2 * s3;
  result(1, 1) = c1 * c3 - c2 * s1 * s3;
  result(2, 1) = s2 * s3;
  result(0, 2) = c1 * s2;
  result(1, 2) = s1 * s2;
  result(2, 2) = c2;

  return result;
}

template <typename T>
inline Matrix<4, 4, T> eulerAnglesZXZ(const T &angle1, const T &angle2,
                                      const T &angle3) {
  T c1 = cos(angle1);
  T s1 = sin(angle1);
  T c2 = cos(angle2);
  T s2 = sin(angle2);
  T c3 = cos(angle3);
  T s3 = sin(angle3);

  Matrix<4, 4, T> result{};
  result(0, 0) = c1 * c3 - c2 * s1 * s3;
  result(1, 0) = c3 * s1 + c1 * c2 * s3;
  result(2, 0) = s2 * s3;
  result(0, 1) = -c1 * s3 - c2 * c3 * s1;
  result(1, 1) = c1 * c2 * c3 - s1 * s3;
  result(2, 1) = c3 * s2;
  result(0, 2) = s1 * s2;
  result(1, 2) = -c1 * s2;
  result(2, 2) = c2;

  return result;
}

template <typename T>
inline Matrix<4, 4, T> eulerAnglesXZY(const T &angle1, const T &angle2,
                                      const T &angle3) {
  T c1 = cos(angle1);
  T s1 = sin(angle1);
  T c2 = cos(angle2);
  T s2 = sin(angle2);
  T c3 = cos(angle3);
  T s3 = sin(angle3);

  Matrix<4, 4, T> result{};
  result(0, 0) = c2 * c3;
  result(1, 0) = s1 * s3 + c1 * c3 * s2;
  result(2, 0) = c3 * s1 * s2 - c1 * s3;
  result(0, 1) = -s2;
  result(1, 1) = c1 * c2;
  result(2, 1) = c2 * s1;
  result(0, 2) = c2 * s3;
  result(1, 2) = c1 * s2 * s3 - c3 * s1;
  result(2, 2) = c1 * c3 + s1 * s2 * s3;

  return result;
}

template <typename T>
inline Matrix<4, 4, T> eulerAnglesYZX(const T &angle1, const T &angle2,
                                      const T &angle3) {
  T c1 = cos(angle1);
  T s1 = sin(angle1);
  T c2 = cos(angle2);
  T s2 = sin(angle2);
  T c3 = cos(angle3);
  T s3 = sin(angle3);

  Matrix<4, 4, T> result{};
  result(0, 0) = c1 * c2;
  result(1, 0) = s2;
  result(2, 0) = -c2 * s1;
  result(0, 1) = s1 * s3 - c1 * c3 * s2;
  result(1, 1) = c2 * c3;
  result(2, 1) = c1 * s3 + c3 * s1 * s2;
  result(0, 2) = c3 * s1 + c1 * s2 * s3;
  result(1, 2) = -c2 * s3;
  result(2, 2) = c1 * c3 - s1 * s2 * s3;

  return result;
}

template <typename T>
inline Matrix<4, 4, T> eulerAnglesZYX(const T &angle1, const T &angle2,
                                      const T &angle3) {
  T c1 = cos(angle1);
  T s1 = sin(angle1);
  T c2 = cos(angle2);
  T s2 = sin(angle2);
  T c3 = cos(angle3);
  T s3 = sin(angle3);

  Matrix<4, 4, T> result{};
  result(0, 0) = c1 * c2;
  result(1, 0) = c2 * s1;
  result(2, 0) = -s2;
  result(0, 1) = c1 * s2 * s3 - c3 * s1;
  result(1, 1) = c1 * c3 + s1 * s2 * s3;
  result(2, 1) = c2 * s3;
  result(0, 2) = s1 * s3 + c1 * c3 * s2;
  result(1, 2) = c3 * s1 * s2 - c1 * s3;
  result(2, 2) = c2 * c3;

  return result;
}

template <typename T>
inline Matrix<4, 4, T> eulerAnglesZXY(const T &angle1, const T &angle2,
                                      const T &angle3) {
  T c1 = cos(angle1);
  T s1 = sin(angle1);
  T c2 = cos(angle2);
  T s2 = sin(angle2);
  T c3 = cos(angle3);
  T s3 = sin(angle3);

  Matrix<4, 4, T> result{};
  result(0, 0) = c1 * c3 - s1 * s2 * s3;
  result(1, 0) = c3 * s1 + c1 * s2 * s3;
  result(2, 0) = -c2 * s3;
  result(0, 1) = -c2 * s1;
  result(1, 1) = c1 * c2;
  result(2, 1) = s2;
  result(0, 2) = c1 * s3 + c3 * s1 * s2;
  result(1, 2) = s1 * s3 - c1 * c3 * s2;
  result(2, 2) = c2 * c3;

  return result;
}

template <typename T>
inline Matrix<4, 4, T> eulerAnglesRotate(const T &yaw, const T &pitch,
                                         const T &roll) {
  T cy = cos(yaw);
  T sy = sin(yaw);
  T cp = cos(pitch);
  T sp = sin(pitch);
  T cr = cos(roll);
  T sr = sin(roll);

  Matrix<4, 4, T> result{};
  result(0, 0) = cy * cr + sy * sp * sr;
  result(1, 0) = sr * cp;
  result(2, 0) = -sy * cr + cy * sp * sr;
  result(0, 1) = -cy * sr + sy * sp * cr;
  result(1, 1) = cr * cp;
  result(2, 1) = sr * sy + cy * sp * cr;
  result(0, 2) = sy * cp;
  result(1, 2) = -sp;
  result(2, 2) = cy * cp;

  return result;
}

template <typename T>
inline void extractEulerAnglesXYZ(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3) {
  T at1 = atan2<T>(m(1, 2), m(2, 2));
  T c2 = sqrt(m(0, 0) * m(0, 0) + m(0, 1) * m(0, 1));
  T at2 = atan2<T>(-m(0, 2), c2);
  T s1 = sin(at1);
  T c1 = cos(at1);
  T at3 = atan2<T>(s1 * m(2, 0) - c1 * m(1, 0), c1 * m(1, 1) - s1 * m(2, 1));
  angle1 = -at1;
  angle2 = -at2;
  angle3 = -at3;
}

template <typename T>
inline void extractEulerAnglesYXZ(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3) {
  T at1 = atan2<T>(m(0, 2), m(2, 2));
  T c2 = sqrt(m(1, 0) * m(1, 0) + m(1, 1) * m(1, 1));
  T at2 = atan2<T>(-m(1, 2), c2);
  T s1 = sin(at1);
  T c1 = cos(at1);
  T at3 = atan2<T>(s1 * m(2, 1) - c1 * m(0, 1), c1 * m(0, 0) - s1 * m(2, 0));
  angle1 = at1;
  angle2 = at2;
  angle3 = at3;
}

template <typename T>
inline void extractEulerAnglesXZX(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3) {
  T at1 = atan2<T>(m(2, 0), m(1, 0));
  T s2 = sqrt(m(0, 1) * m(0, 1) + m(0, 2) * m(0, 2));
  T at2 = atan2<T>(s2, m(0, 0));
  T s1 = sin(at1);
  T c1 = cos(at1);
  T at3 = atan2<T>(c1 * m(2, 1) - s1 * m(1, 1), c1 * m(2, 2) - s1 * m(1, 2));
  angle1 = at1;
  angle2 = at2;
  angle3 = at3;
}

template <typename T>
inline void extractEulerAnglesXYX(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3) {
  T at1 = atan2<T>(m(1, 0), -m(2, 0));
  T s2 = sqrt(m(0, 1) * m(0, 1) + m(0, 2) * m(0, 2));
  T at2 = atan2<T>(s2, m(0, 0));
  T s1 = sin(at1);
  T c1 = cos(at1);
  T at3 = atan2<T>(-c1 * m(1, 2) - s1 * m(2, 2), c1 * m(1, 1) + s1 * m(2, 1));
  angle1 = at1;
  angle2 = at2;
  angle3 = at3;
}

template <typename T>
inline void extractEulerAnglesYXY(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3) {
  T at1 = atan2<T>(m(0, 1), m(2, 1));
  T s2 = sqrt(m(1, 0) * m(1, 0) + m(1, 2) * m(1, 2));
  T at2 = atan2<T>(s2, m(1, 1));
  T s1 = sin(at1);
  T c1 = cos(at1);
  T at3 = atan2<T>(c1 * m(0, 2) - s1 * m(2, 2), c1 * m(0, 0) - s1 * m(2, 0));
  angle1 = at1;
  angle2 = at2;
  angle3 = at3;
}

template <typename T>
inline void extractEulerAnglesYZY(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3) {
  T at1 = atan2<T>(m(2, 1), -m(0, 1));
  T s2 = sqrt(m(1, 0) * m(1, 0) + m(1, 2) * m(1, 2));
  T at2 = atan2<T>(s2, m(1, 1));
  T s1 = sin(at1);
  T c1 = cos(at1);
  T at3 = atan2<T>(-s1 * m(0, 0) - c1 * m(2, 0), s1 * m(0, 2) + c1 * m(2, 2));
  angle1 = at1;
  angle2 = at2;
  angle3 = at3;
}

template <typename T>
inline void extractEulerAnglesZYZ(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3) {
  T at1 = atan2<T>(m(1, 2), m(0, 2));
  T s2 = sqrt(m(2, 0) * m(2, 0) + m(2, 1) * m(2, 1));
  T at2 = atan2<T>(s2, m(2, 2));
  T s1 = sin(at1);
  T c1 = cos(at1);
  T at3 = atan2<T>(c1 * m(1, 0) - s1 * m(0, 0), c1 * m(1, 1) - s1 * m(0, 1));
  angle1 = at1;
  angle2 = at2;
  angle3 = at3;
}

template <typename T>
inline void extractEulerAnglesZXZ(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3) {
  T at1 = atan2<T>(m(0, 2), -m(1, 2));
  T s2 = sqrt(m(2, 0) * m(2, 0) + m(2, 1) * m(2, 1));
  T at2 = atan2<T>(s2, m(2, 2));
  T s1 = sin(at1);
  T c1 = cos(at1);
  T at3 = atan2<T>(-c1 * m(0, 1) - s1 * m(1, 1), c1 * m(0, 0) + s1 * m(1, 0));
  angle1 = at1;
  angle2 = at2;
  angle3 = at3;
}

template <typename T>
inline void extractEulerAnglesXZY(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3) {
  T at1 = atan2<T>(m(2, 1), m(1, 1));
  T c2 = sqrt(m(0, 0) * m(0, 0) + m(0, 2) * m(0, 2));
  T at2 = atan2<T>(-m(1, 0), c2);
  T s1 = sin(at1);
  T c1 = cos(at1);
  T at3 = atan2<T>(s1 * m(1, 0) - c1 * m(2, 0), c1 * m(2, 2) - s1 * m(1, 2));
  angle1 = at1;
  angle2 = at2;
  angle3 = at3;
}

template <typename T>
inline void extractEulerAnglesYZX(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3) {
  T at1 = atan2<T>(-m(2, 0), m(0, 0));
  T c2 = sqrt(m(1, 1) * m(1, 1) + m(1, 2) * m(1, 2));
  T at2 = atan2<T>(m(0, 1), c2);
  T s1 = sin(at1);
  T c1 = cos(at1);
  T at3 = atan2<T>(s1 * m(0, 1) + c1 * m(2, 1), s1 * m(0, 2) + c1 * m(2, 2));
  angle1 = at1;
  angle2 = at2;
  angle3 = at3;
}

template <typename T>
inline void extractEulerAnglesZYX(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3) {
  T at1 = atan2<T>(m(1, 0), m(0, 0));
  T c2 = sqrt(m(2, 1) * m(2, 1) + m(2, 2) * m(2, 2));
  T at2 = atan2<T>(-m(2, 0), c2);
  T s1 = sin(at1);
  T c1 = cos(at1);
  T at3 = atan2<T>(s1 * m(0, 2) - c1 * m(1, 2), c1 * m(1, 1) - s1 * m(0, 1));
  angle1 = at1;
  angle2 = at2;
  angle3 = at3;
}

template <typename T>
inline void extractEulerAnglesZXY(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3) {
  T at1 = atan2<T>(-m(0, 1), m(1, 1));
  T c2 = sqrt(m(2, 0) * m(2, 0) + m(2, 2) * m(2, 2));
  T at2 = atan2<T>(m(2, 1), c2);
  T s1 = sin(at1);
  T c1 = cos(at1);
  T at3 = atan2<T>(c1 * m(0, 2) + s1 * m(1, 2), c1 * m(0, 0) + s1 * m(1, 0));
  angle1 = at1;
  angle2 = at2;
  angle3 = at3;
}
}  // namespace Neat