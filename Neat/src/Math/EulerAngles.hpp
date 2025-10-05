#pragma once

#include "Types/TypeMatrixMxN.hpp"

namespace Neat {
template <typename T>
inline Matrix<4, 4, T> eulerAnglesXYZ(const T &angle1, const T &angle2,
                                      const T &angle3);

template <typename T>
inline Matrix<4, 4, T> eulerAnglesYXZ(const T &yaw, const T &pitch,
                                      const T &roll);

template <typename T>
inline Matrix<4, 4, T> eulerAnglesXZX(const T &angle1, const T &angle2,
                                      const T &angle3);

template <typename T>
inline Matrix<4, 4, T> eulerAnglesXYX(const T &angle1, const T &angle2,
                                      const T &angle);

template <typename T>
inline Matrix<4, 4, T> eulerAnglesYXY(const T &angle1, const T &angle2,
                                      const T &angle3);

template <typename T>
inline Matrix<4, 4, T> eulerAnglesYZY(const T &angle1, const T &angle2,
                                      const T &angle3);

template <typename T>
inline Matrix<4, 4, T> eulerAnglesZYZ(const T &angle1, const T &angle2,
                                      const T &angle3);

template <typename T>
inline Matrix<4, 4, T> eulerAnglesZXZ(const T &angle1, const T &angle2,
                                      const T &angle3);

template <typename T>
inline Matrix<4, 4, T> eulerAnglesXZY(const T &angle1, const T &angle2,
                                      const T &angle3);

template <typename T>
inline Matrix<4, 4, T> eulerAnglesYZX(const T &angle1, const T &angle2,
                                      const T &angle3);

template <typename T>
inline Matrix<4, 4, T> eulerAnglesZYX(const T &angle1, const T &angle2,
                                      const T &angle3);

template <typename T>
inline Matrix<4, 4, T> eulerAnglesZXY(const T &angle1, const T &angle2,
                                      const T &angle3);

template <typename T>
inline Matrix<4, 4, T> eulerAnglesRotate(const T &yaw, const T &pitch,
                                         const T &roll);

template <typename T>
inline void extractEulerAnglesXYZ(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3);

template <typename T>
inline void extractEulerAnglesYXZ(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3);

template <typename T>
inline void extractEulerAnglesXZX(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3);

template <typename T>
inline void extractEulerAnglesXYX(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3);

template <typename T>
inline void extractEulerAnglesYXY(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3);

template <typename T>
inline void extractEulerAnglesYZY(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3);

template <typename T>
inline void extractEulerAnglesZYZ(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3);

template <typename T>
inline void extractEulerAnglesZXZ(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3);

template <typename T>
inline void extractEulerAnglesXZY(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3);

template <typename T>
inline void extractEulerAnglesYZX(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3);

template <typename T>
inline void extractEulerAnglesZYX(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3);

template <typename T>
inline void extractEulerAnglesZXY(Matrix<4, 4, T> const &m, T &angle1,
                                  T &angle2, T &angle3);
}  // namespace Neat

#include "Math/EulerAngles.inl"