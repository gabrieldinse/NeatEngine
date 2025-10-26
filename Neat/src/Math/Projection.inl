#include <cmath>

namespace Neat {
template <typename T>
Matrix<4, 4, T> orthographicProjection(const T &left, const T &right,
                                       const T &bottom, const T &top,
                                       const T &near, const T &far) {
  Matrix<4, 4, T> result(One<T>);

  result[0][0] = Two<T> / (right - left);
  result[1][1] = Two<T> / (top - bottom);
  result[2][2] = -Two<T> / (far - near);
  result[0][3] = -(right + left) / (right - left);
  result[1][3] = -(top + bottom) / (top - bottom);
  result[2][3] = -(far + near) / (far - near);

  return result;
}

template <typename T>
Matrix<4, 4, T> perspectiveProjection(const T &fieldOfView,
                                      const T &aspectRatio, const T &near,
                                      const T &far) {
  Matrix<4, 4, T> result(One<T>);

  T tan_half_fov = std::tan(fieldOfView / Two<T>);
  result[0][0] = One<T> / (aspectRatio * tan_half_fov);
  result[1][1] = One<T> / tan_half_fov;
  result[2][2] = -(far + near) / (far - near);
  result[2][3] = -Two<T> * far * near / (far - near);
  result[3][2] = -One<T>;
  result[3][3] = Zero<T>;

  return result;
}

template <typename T>
Matrix<4, 4, T> lookAtRightHandView(const Vector<3, T> &eye,
                                    const Vector<3, T> &target,
                                    const Vector<3, T> &upDirection) {
  Vector<3, T> front(normalize(target - eye));
  Vector<3, T> right(normalize(cross(front, upDirection)));
  Vector<3, T> up(cross(right, front));

  return Matrix<4, 4, T>(right.x(), right.y, right.z, -dot(eye, right), up.x(),
                         up.y, up.z, -dot(eye, up), -front.x(), -front.y,
                         -front.z, dot(eye, front), 0, 0, 0, 1);
}

template <typename T>
Matrix<4, 4, T> lookAtLeftHandView(const Vector<3, T> &eye,
                                   const Vector<3, T> &target,
                                   const Vector<3, T> &upDirection) {
  Vector<3, T> front(normalize(target - eye));
  Vector<3, T> right(normalize(cross(upDirection, front)));
  Vector<3, T> up(cross(front, right));

  return Matrix<4, 4, T>(right.x(), right.y(), right.z(), -dot(eye, right),
                         up.x(), up.y(), up.z(), -dot(eye, up), front.x(),
                         front.y(), front.z(), -dot(eye, front), 0, 0, 0, 1);
}
}  // namespace Neat