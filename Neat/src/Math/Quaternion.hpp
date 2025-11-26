#pragma once

#include <iostream>

#include "Types/TypeQuaternion.hpp"

namespace fmt {
template <typename T>
struct formatter<Neat::Quaternion<T>> {
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  template <typename Context>
  auto format(const Neat::Quaternion<T>& q, Context& ctx) const {
    std::string str =
        fmt::format("Quaternion{{{}, {}, {}, {}}}", q.w(), q.x(), q.y(), q.z());
    return format_to(ctx.out(), "{}", str);
  }
};
}  // namespace fmt

namespace Neat {
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Quaternion<T>& q) {
  os << fmt::format("{}", q);
  return os;
}
}  // namespace Neat