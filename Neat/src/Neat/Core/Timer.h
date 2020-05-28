#pragma once

#include <chrono>
#include <utility>

#include "Neat/Core/Types.h"
#include "Neat/Core/Exceptions.h"


namespace Neat
{
   enum class TimeUnit : UIntShort
   {
      None = 0,
      Nanoseconds, Microseconds, Milliseconds, Seconds,
      Minutes, Hours, Days
   };

   class Timer
   {
   public:
      Timer() = default;

      void start()
      {
         m_startTicks = std::chrono::high_resolution_clock::now();

         if (!m_started)
            m_started = true;
      }

      template <typename T = double>
      T stop(TimeUnit timeUnit = TimeUnit::Seconds)
      {
         auto time_passed = elapsed<T>(timeUnit);
         m_started = false;

         return time_passed;
      }

      template <typename T = double>
      T restart(TimeUnit timeUnit = TimeUnit::Seconds)
      {
         auto time_passed = elapsed<T>(timeUnit);
         m_startTicks = m_currentTicks;

         return time_passed;
      }

      template <typename T = double>
      T elapsed(TimeUnit timeUnit = TimeUnit::Seconds)
      {
         if (m_started)
         {
            m_currentTicks = std::chrono::high_resolution_clock::now();

            switch (timeUnit)
            {
               case TimeUnit::Nanoseconds:    return nanosecondsPassed<T>();
               case TimeUnit::Microseconds:   return microsecondsPassed<T>();
               case TimeUnit::Milliseconds:   return millisecondsPassed<T>();
               case TimeUnit::Seconds:        return secondsPassed<T>();
               case TimeUnit::Minutes:        return minutesPassed<T>();
               case TimeUnit::Hours:          return hoursPassed<T>();
               case TimeUnit::Days:           return daysPassed<T>();
            }

            throw WrongTimeUnitError();
         }

         throw StopwatchNotStartedError();
      }

   private:
      template <typename T>
      T nanosecondsPassed() const
      {
         return
            std::chrono::duration<T, std::ratio<1, 1000000000>>(
               (m_currentTicks - m_startTicks)).count();
      }

      template <typename T>
      T microsecondsPassed() const
      {
         return
            std::chrono::duration<T, std::ratio<1, 1000000>>(
               (m_currentTicks - m_startTicks)).count();
      }

      template <typename T>
      T millisecondsPassed() const
      {
         return
            std::chrono::duration<T, std::ratio<1, 1000>>(
               (m_currentTicks - m_startTicks)).count();
      }

      template <typename T>
      T secondsPassed() const
      {
         return
            std::chrono::duration<T>((m_currentTicks - m_startTicks)).count();
      }

      template <typename T>
      T minutesPassed() const
      {
         return
            std::chrono::duration<T, std::ratio<60, 1>>(
               (m_currentTicks - m_startTicks)).count();
      }

      template <typename T>
      T hoursPassed() const
      {
         return
            std::chrono::duration<T, std::ratio<3600, 1>>(
               (m_currentTicks - m_startTicks)).count();
      }

      template <typename T>
      T daysPassed() const
      {
         return
            std::chrono::duration<T, std::ratio<86400, 1>>(
               (m_currentTicks - m_startTicks)).count();
      }

   private:
      std::chrono::steady_clock::time_point m_startTicks;
      std::chrono::steady_clock::time_point m_currentTicks;
      bool m_started = false;
   };
}