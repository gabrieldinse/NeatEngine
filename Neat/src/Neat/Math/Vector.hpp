#pragma once

#include <iostream>

#include "Neat/Math/Types/Vector1.hpp"
#include "Neat/Math/Types/Vector2.hpp"
#include "Neat/Math/Types/Vector3.hpp"
#include "Neat/Math/Types/Vector4.hpp"

#include <spdlog/fmt/bundled/core.h>

namespace fmt {
template <Neat::UInt32 N, typename T>
struct formatter<Neat::Vector<N, T>> {
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  template <typename Context>
  auto format(const Neat::Vector<N, T>& v, Context& ctx) const {
    std::string str = fmt::format("Vector{}{{", N);
    for (Neat::UInt32 i = 0; i < N; ++i) {
      str += fmt::format("{}", v[i]);
      if (i < N - 1) {
        str += ", ";
      }
    }
    str += "}";
    return format_to(ctx.out(), "{}", str);
  }
};
}  // namespace fmt

namespace Neat {
template <UInt32 N, typename T>
std::ostream& operator<<(std::ostream& os, const Vector<N, T>& v) {
  os << fmt::format("{}", v);
  return os;
}
}  // namespace Neat