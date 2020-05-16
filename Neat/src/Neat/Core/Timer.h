#pragma once

#include <chrono>

#include "Neat/Core/Types.h"


namespace Neat
{
   class Timer
   {
   public:
      Timer() = default;

      void start()
      {
         m_startTicks = std::chrono::high_resolution_clock::now();
      }

      void reset()
      {
         auto current_ticks = std::chrono::high_resolution_clock::now();
         m_deltaTime = 
            std::chrono::duration_cast<std::chrono::duration<Timestep>>(
            (current_ticks - m_startTicks)).count();
         m_startTicks = current_ticks;
      }

      Timestep getDeltaTime() const { return m_deltaTime; }

   private:
      std::chrono::steady_clock::time_point m_startTicks;
      Timestep m_deltaTime = 0.0f;
   };
}