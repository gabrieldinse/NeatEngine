#pragma once

#include "Neat/Math/Types/TypeMatrixMxN.hpp"
#include "Neat/Math/Types/TypeVectorN.hpp"

namespace Neat {
// Vector
template <typename T> Matrix<4, 4, T> translate(const Vector<3, T> &v);

template <typename T>
Matrix<4, 4, T> translate(const Matrix<4, 4, T> &m, const Vector<3, T> &v);

template <typename T>
Matrix<4, 4, T> rotate(const T &angleRadians, const Vector<3, T> &rotationAxis);

template <typename T>
Matrix<4, 4, T> rotate(const Matrix<4, 4, T> &m, const T &angleRadians,
                       const Vector<3, T> &rotationAxis);

template <typename T> inline Matrix<4, 4, T> rotateX(const T &angleRadians);

template <typename T> inline Matrix<4, 4, T> rotateY(const T &angleRadians);

template <typename T> inline Matrix<4, 4, T> rotateZ(const T &angleRadians);

template <typename T> Matrix<4, 4, T> scale(const Vector<3, T> &v);

template <typename T>
Matrix<4, 4, T> scale(const Matrix<4, 4, T> &m, const Vector<3, T> &v);

// Quaternion
template <typename T>
Quaternion<T> rotate(const Quaternion<T> &q, const T &angleRadians,
                     const Vector<3, T> &rotationAxis);
} // namespace Neat

#include "Neat/Math/Transform.inl"