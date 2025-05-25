#include "Neat/Helper/FPSCounter.hpp"
#include "Neat/Core/Log.hpp"

namespace Neat {
void FPSCounter::addFrame() {
  ++m_frameCount;

  if (timer.elapsed() > m_interval) {
    timer.restart();
    m_fps = m_frameCount / m_interval;
    m_frameCount = 0;
    NT_CORE_TRACE("FPS: {0}", m_fps);
  }
}
} // namespace Neat