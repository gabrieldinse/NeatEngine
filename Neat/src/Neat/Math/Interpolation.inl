

namespace Neat {
// Scalar
template <typename T, typename U>
inline constexpr T mix(const T &a, const T &b, const U &t) {
  return a * (one<T> - static_cast<T>(t)) + b * static_cast<T>(t);
}

// Vector
template <UInt32 N, typename T, typename U>
inline constexpr Vector<N, T> mix(const Vector<N, T> &a, const Vector<N, T> &b,
                                  const U &t) {
  return a * (one<T> - static_cast<T>(t)) + b * static_cast<T>(t);
}

template <UInt32 N, typename T, typename U>
inline constexpr Vector<N, T>
quadraticBezier(const Vector<N, T> &a, const Vector<N, T> &b,
                const Vector<N, T> &c, const U &t) {
  auto d = mix(a, b, t);
  auto e = mix(b, c, t);
  auto p = mix(d, e, t);

  return p;
}

template <UInt32 N, typename T, typename U>
inline constexpr Vector<N, T>
cubicBezier(const Vector<N, T> &a, const Vector<N, T> &b, const Vector<N, T> &c,
            const Vector<N, T> &d, const U &t) {
  auto e = mix(a, b, t);
  auto f = mix(b, c, t);
  auto g = mix(c, d, t);

  auto h = mix(e, f, t);
  auto i = mix(f, g, t);
  auto p = mix(h, i, t);

  return p;
}

// Quaternion
template <typename T, typename U>
constexpr Quaternion<T> mix(const Quaternion<T> &a, const Quaternion<T> &b,
                            const U &t) {
  T cos_theta = dot(a, b);

  // Performs linear interpolation when cos_theta is close to 1 to avoid
  // sin(angle) to become a division by 0
  if (cos_theta > one<T> - epsilon<T>)
    return Quaternion<T>(mix(a.w, b.w), mix(a.v, b.v));

  T angle = acos(cos_theta);
  return (sin((one<T> - static_cast<T>(t)) * angle) * a +
          sin(static_cast<T>(t) * angle) * b) /
         sin(angle);
}

template <typename T, typename U>
constexpr Quaternion<T> lerp(const Quaternion<T> &a, const Quaternion<T> &b,
                             const U &t) {
  if (t < zero<T> || t > one<T>)
    throw QuaternionLerpStepError();

  return a * (one<T> - static_cast<T>(t)) + b * static_cast<T>(t);
}

template <typename T, typename U>
constexpr Quaternion<T> slerp(const Quaternion<T> &a, const Quaternion<T> &b,
                              const U &t) {
  T cos_theta = dot(a, b);
  Quaternion<T> c(b);

  // If cos_theta is negative, slerp will take the longest path
  // The solution is to invert one of the quaternions (a or b) and so we
  // get a positive dot product
  if (cos_theta < zero<T>) {
    c = -b;
    cos_theta = -cos_theta;
  }

  // Performs linear interpolation when cos_theta is close to 1 to avoid
  // sin(angle) to become a division by 0
  if (cos_theta > one<T> - epsilon<T>)
    return Quaternion<T>(mix(a.w, b.w), mix(a.v, b.v));

  T angle = acos(cos_theta);

  return (sin((one<T> - static_cast<T>(t)) * angle) * a +
          sin(static_cast<T>(t) * angle) * c) /
         sin(angle);
}
} // namespace Neat