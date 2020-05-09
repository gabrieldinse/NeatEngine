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
         this->startTicks = std::chrono::high_resolution_clock::now();
      }

      void reset()
      {
         auto current_ticks = std::chrono::high_resolution_clock::now();
         this->deltaTime = 
            std::chrono::duration_cast<std::chrono::duration<Float>>(
            (current_ticks - this->startTicks)).count();
         this->startTicks = current_ticks;
      }

      Float getDeltaTime() const { return this->deltaTime; }

   private:
      std::chrono::steady_clock::time_point startTicks;
      Float deltaTime = 0.0f;
   };
}