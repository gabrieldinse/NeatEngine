#pragma once

#include <array>
#include <iterator>
#include <numeric>

#include "Neat/Core/Exceptions.hpp"
#include "Neat/Core/Timer.hpp"
#include "Neat/Core/Types.hpp"

namespace Neat {
class FPSCounter {
 public:
  FPSCounter(double intervalSeconds = 1.0) : m_interval(intervalSeconds) {}

  void start() { timer.start(); }
  double getFPS() const { return m_fps; }

  void addFrame();

 private:
  double m_interval;
  double m_fps = 0.0;
  Timer timer;
  UInt32 m_frameCount = 0;
};
}  // namespace Neat
