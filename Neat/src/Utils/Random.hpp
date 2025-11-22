#pragma once

#include <random>
#include <mutex>

namespace Neat {
class Random {
 public:
  Random(const Random&) = delete;
  Random& operator=(const Random&) = delete;
  Random(Random&&) = delete;
  Random& operator=(Random&&) = delete;

  static Random& getInstance() {
    static Random instance;
    return instance;
  }

  float getFloat(float min = 0.0f, float max = 1.0f) {
    std::lock_guard<std::mutex> lock{m_mutex};
    std::uniform_real_distribution<float> distribution{min, max};
    return distribution(m_engine);
  }

 private:
  Random() = default;

 private:
  std::mt19937 m_engine{std::random_device{}()};
  std::mutex m_mutex;
};
};  // namespace Neat