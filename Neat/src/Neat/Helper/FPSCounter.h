#pragma once

#include <array>
#include <numeric>
#include <iterator>

#include "Neat/Core/Types.h"
#include "Neat/Core/Exceptions.h"
#include "Neat/Core/Stopwatch.h"


namespace Neat
{
   class FPSCounter
   {
   public:
      FPSCounter(double intervalSeconds = 1.0) : m_interval(intervalSeconds) {}
      void start() { m_stopwatch.start(); }

      void addFrame()
      {
         ++m_frameCount;

         if (m_stopwatch.mark() > m_interval)
         {
            m_stopwatch.restart();
            m_fps = m_frameCount / m_interval;
            m_frameCount = 0;
            NT_CORE_TRACE("FPS: {0}", m_fps);
         }
      }

      double getFPS() const { return m_fps; }

   private:
      double m_interval;
      double m_fps = 0.0;
      Stopwatch m_stopwatch;
      UInt m_frameCount = 0;
   };
}
