#pragma once

#include <iostream>

#include "Types/Matrix2x2.hpp"
#include "Types/Matrix3x3.hpp"
#include "Types/Matrix4x4.hpp"

#include <spdlog/fmt/bundled/core.h>

namespace fmt {
template <Neat::UInt32 M, Neat::UInt32 N, typename T>
struct formatter<Neat::Matrix<M, N, T>> {
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  template <typename Context>
  auto format(const Neat::Matrix<M, N, T>& m, Context& ctx) const {
    std::string str = fmt::format("Matrix{}{}{{", M, N);
    for (Neat::UInt32 i = 0; i < M; ++i) {
      for (Neat::UInt32 j = 0; j < N; ++j) {
        str += fmt::format("{}", m(i, j));
        if (j < N - 1) {
          str += ", ";
        }
      }
      if (i < M - 1) {
        str += ", ";
      }
    }
    str += "}";
    return format_to(ctx.out(), "{}", str);
  }
};
}  // namespace fmt

namespace Neat {
template <UInt32 M, UInt32 N, typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<M, N, T>& m) {
  os << fmt::format("{}", m);
  return os;
}
}  // namespace Neat