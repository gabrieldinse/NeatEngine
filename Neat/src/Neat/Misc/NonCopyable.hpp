#pragma once

namespace Neat {
class NonCopyable {
 protected:
  NonCopyable() = default;
  ~NonCopyable() = default;

  NonCopyable(const NonCopyable &) = delete;
  NonCopyable &operator=(const NonCopyable &) = delete;
};
}  // namespace Neat