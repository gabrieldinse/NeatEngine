#pragma once

#include "Neat/Core/Timer.hpp"
#include "Neat/Debug/Instrumentor.hpp"

namespace Neat {
class InstrumentationTimer {
 public:
  InstrumentationTimer(const std::string &name) : m_name(name) {
    m_timer.start();
  }

  ~InstrumentationTimer() { stop(); }

  void stop() {
    if (m_timer.started()) {
      double elapsed = m_timer.stop(TimeUnit::Microseconds);
      Instrumentor::get().writeProfile(
          {m_name, m_timer.startTimeSinceEpoch(TimeUnit::Microseconds), elapsed,
           std::this_thread::get_id()});
    }
  }

 private:
  std::string m_name;
  Timer m_timer;
};

}  // namespace Neat