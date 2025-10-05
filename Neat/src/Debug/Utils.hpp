#pragma once

#include "Core/Types.hpp"

namespace Neat {
template <size_t N>
struct ChangeResult {
  char data[N];
};

template <size_t N, size_t K>
constexpr auto cleanupOutputString(const char (&expression)[N],
                                   const char (&remove)[K]) {
  ChangeResult<N> result = {};

  size_t source_index = 0;
  size_t destination_index = 0;
  while (source_index < N) {
    size_t match_index = 0;
    while (match_index < K - 1 && source_index + match_index < N - 1 &&
           expression[source_index + match_index] == remove[match_index])
      match_index++;
    if (match_index == K - 1) source_index += match_index;
    result.data[destination_index++] =
        expression[source_index] == '"' ? '\'' : expression[source_index];
    source_index++;
  }
  return result;
}
}  // namespace Neat