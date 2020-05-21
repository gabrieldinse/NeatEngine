#pragma once

#include <chrono>

#include "Neat/Core/Types.h"


namespace Neat
{
   class Chronometer
   {
   public:
      Chronometer() = default;

      void start()
      {
         m_startTicks = std::chrono::high_resolution_clock::now();
      }

      void restart()
      {
         start();
      }

      double restartAndGetSeconds()
      {
         auto seconds_passed = secondsPassed();
         m_startTicks = m_currentTicks;

         return seconds_passed;
      }

      double restartAndGetMilliseconds()
      {
         auto seconds_passed = millisecondsPassed();
         m_startTicks = m_currentTicks;

         return seconds_passed;
      }

      double restartAndGetNanoseconds()
      {
         auto seconds_passed = nanosecondsPassed();
         m_startTicks = m_currentTicks;

         return seconds_passed;
      }

      double restartAndGetMinutes()
      {
         auto seconds_passed = minutesPassed();
         m_startTicks = m_currentTicks;

         return seconds_passed;
      }

      double secondsPassed()
      {
         m_currentTicks = std::chrono::high_resolution_clock::now();

         return 
            std::chrono::duration<double>(
               (m_currentTicks - m_startTicks)).count();
      }

      double millisecondsPassed()
      {
         m_currentTicks = std::chrono::high_resolution_clock::now();

         return 
            std::chrono::duration<double, std::milli>(
               (m_currentTicks - m_startTicks)).count();
      }

      double nanosecondsPassed()
      {
         m_currentTicks = std::chrono::high_resolution_clock::now();

         return 
            std::chrono::duration<double, std::nano>(
               (m_currentTicks - m_startTicks)).count();
      }

      double minutesPassed()
      {
         return secondsPassed() / 60.0;
      }

   private:
      std::chrono::steady_clock::time_point m_startTicks;
      std::chrono::steady_clock::time_point m_currentTicks;
   };
}