#include "Neat/Helper/FPSCounter.h"
#include "Neat/Core/Log.h"


namespace Neat
{
   void FPSCounter::addFrame()
   {
      ++m_frameCount;

      if (timer.elapsed() > m_interval)
      {
         timer.restart();
         m_fps = m_frameCount / m_interval;
         m_frameCount = 0;
         NT_CORE_TRACE("FPS: {0}", m_fps);
      }
   }
}