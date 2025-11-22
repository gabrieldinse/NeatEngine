#pragma once

#include "Core/Timer.hpp"
#include "Core/Types.hpp"

namespace Neat {
class FPSCounter {
 public:
  FPSCounter(double refreshRate = 1.0) : m_refreshRateSeconds(refreshRate) {}

  void start() {
    if (not started) {
      timer.start();
      started = true;
    }
  }
  double getFPS() const { return m_fps; }

  void addFrame();

 private:
  double m_refreshRateSeconds;
  double m_fps = 0.0;
  Timer timer;
  UInt32 m_frameCount = 0;
  bool started = false;
};
}  // namespace Neat
