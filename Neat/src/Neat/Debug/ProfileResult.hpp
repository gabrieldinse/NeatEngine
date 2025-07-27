#pragma once

#include <string>
#include <thread>

namespace Neat {
struct ProfileResult {
  std::string name;
  double startTime;
  double elapsedTime;
  std::thread::id threadID;
};
}  // namespace Neat