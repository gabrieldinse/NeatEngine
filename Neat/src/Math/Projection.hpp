#pragma once

#include "Types/TypeMatrixMxN.hpp"

namespace Neat {
template <typename T>
Matrix<4, 4, T> orthographicProjection(const T &left, const T &right,
                                       const T &bottom, const T &top,
                                       const T &near, const T &far);

template <typename T>
Matrix<4, 4, T> perspectiveProjection(const T &fov, const T &aspectRatio,
                                      const T &near, const T &far);

template <typename T>
Matrix<4, 4, T> lookAtLeftHandView(const Vector<3, T> &eye,
                                   const Vector<3, T> &target,
                                   const Vector<3, T> &upDirection);

template <typename T>
Matrix<4, 4, T> lookAtRightHandView(const Vector<3, T> &eye,
                                    const Vector<3, T> &target,
                                    const Vector<3, T> &upDirection);
}  // namespace Neat

#include "Math/Projection.inl"