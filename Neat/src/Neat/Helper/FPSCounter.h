#pragma once

#include <array>
#include <numeric>
#include <iterator>

#include "Neat/Core/Types.h"
#include "Neat/Core/Exceptions.h"
#include "Neat/Core/Timer.h"


namespace Neat
{
   class FPSCounter
   {
   public:
      FPSCounter(double intervalSeconds = 1.0)
         : m_interval(intervalSeconds) {}

      void start() { timer.start(); }
      double getFPS() const { return m_fps; }

      void addFrame();

   private:
      double m_interval;
      double m_fps = 0.0;
      Timer timer;
      UInt32 m_frameCount = 0;
   };
}
