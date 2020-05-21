#pragma once

#include <array>
#include <numeric>
#include <iterator>

#include "Neat/Core/Types.h"
#include "Neat/Core/Exceptions.h"
#include "Neat/Core/Chronometer.h"


namespace Neat
{
   class FPSCounter
   {
   public:
      FPSCounter(double intervalSeconds = 1.0) : m_interval(intervalSeconds) {}
      void start() { m_chronometer.start(); }

      void addFrame()
      {
         ++m_frameCount;

         if (m_chronometer.getTimePassed() > m_interval)
         {
            m_chronometer.restart();
            m_fps = m_frameCount / m_interval;
            NT_CORE_TRACE("Fps: {0}", m_fps);
            m_frameCount = 0;
         }
      }

      double getFPS() const { return m_fps; }

   private:
      double m_interval;
      double m_fps = 0.0;
      Chronometer m_chronometer;
      UInt m_frameCount = 0;
   };
}
