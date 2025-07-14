#include <cmath>

namespace Neat {
template <typename T>
Matrix<4, 4, T> orthographicProjection(const T &left, const T &right,
                                       const T &bottom, const T &top,
                                       const T &near, const T &far) {
  Matrix<4, 4, T> result(one<T>);

  result[0][0] = two<T> / (right - left);
  result[1][1] = two<T> / (top - bottom);
  result[2][2] = -two<T> / (far - near);
  result[0][3] = -(right + left) / (right - left);
  result[1][3] = -(top + bottom) / (top - bottom);
  result[2][3] = -(far + near) / (far - near);

  return result;
}

template <typename T>
Matrix<4, 4, T> perspectiveProjection(const T &fieldOfView,
                                      const T &aspectRatio, const T &near,
                                      const T &far) {
  Matrix<4, 4, T> result(one<T>);

  T tan_half_fov = std::tan(fieldOfView / two<T>);
  result[0][0] = one<T> / (aspectRatio * tan_half_fov);
  result[1][1] = one<T> / tan_half_fov;
  result[2][2] = -(far + near) / (far - near);
  result[2][3] = -two<T> * far * near / (far - near);
  result[3][2] = -one<T>;
  result[3][3] = zero<T>;

  return result;
}

template <typename T>
Matrix<4, 4, T> lookAtRH(const Vector<3, T> &eye, const Vector<3, T> &target,
                         const Vector<3, T> &upDirection) {
  Vector<3, T> front(normalize(target - eye));
  Vector<3, T> right(normalize(cross(front, upDirection)));
  Vector<3, T> up(cross(right, front));

  return Matrix<4, 4, T>(right.x, right.y, right.z, -dot(eye, right), up.x,
                         up.y, up.z, -dot(eye, up), -front.x, -front.y,
                         -front.z, dot(eye, front), 0, 0, 0, 1);
}

template <typename T>
Matrix<4, 4, T> lookAtLH(const Vector<3, T> &eye, const Vector<3, T> &target,
                         const Vector<3, T> &upDirection) {
  Vector<3, T> front(normalize(target - eye));
  Vector<3, T> right(normalize(cross(upDirection, front)));
  Vector<3, T> up(cross(front, right));

  return Matrix<4, 4, T>(right.x, right.y, right.z, -dot(eye, right), up.x,
                         up.y, up.z, -dot(eye, up), front.x, front.y, front.z,
                         -dot(eye, front), 0, 0, 0, 1);
}
}  // namespace Neat