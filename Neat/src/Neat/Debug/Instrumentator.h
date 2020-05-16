#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <mutex>

#include "Neat/Core/Log.h"


//#define NT_PROFILE


namespace Neat
{
   struct ProfileResult
   {
      std::string name;
      long long start, end;
      std::size_t theadID;
   };

   struct InstrumentationSession
   {
      std::string name;
   };

   class Instrumentor
   {
   public:
      Instrumentor()
         : m_currentSession(nullptr), m_profileCount(0)
      {
      }

      void beginSession(const std::string& name, const std::string& filepath = "results.json")
      {
         m_outputStream.open(filepath);
         writeHeader();
         m_currentSession = new InstrumentationSession{name};
      }

      void endSession()
      {
         writeFooter();
         m_outputStream.close();
         delete m_currentSession;
         m_currentSession = nullptr;
         m_profileCount = 0;
      }

      void writeProfile(const ProfileResult& result)
      {
         m_writingMutex.lock();
         if (m_profileCount++ > 0)
            m_outputStream << ",";

         std::string name = result.name;
         std::replace(name.begin(), name.end(), '"', '\'');

         m_outputStream << "{";
         m_outputStream << "\"cat\":\"function\",";
         m_outputStream << "\"dur\":" << (result.end - result.start) << ",";
         m_outputStream << "\"name\":\"" << name << "\",";
         m_outputStream << "\"ph\":\"X\",";
         m_outputStream << "\"pid\":0,";
         m_outputStream << "\"tid\":" << result.theadID << ",";
         m_outputStream << "\"ts\":" << result.start;
         m_outputStream << "}";

         m_outputStream.flush();
         m_writingMutex.unlock();
      }

      void writeHeader()
      {
         m_outputStream << "{\"otherData\": {},\"traceEvents\":[";
         m_outputStream.flush();
      }

      void writeFooter()
      {
         m_outputStream << "]}";
         m_outputStream.flush();
      }

      static Instrumentor& get()
      {
         static Instrumentor s_instance;
         return s_instance;
      }

   private:
      InstrumentationSession* m_currentSession;
      std::ofstream m_outputStream;
      Int m_profileCount;
      std::mutex m_writingMutex;
   };

   class InstrumentationTimer
   {
   public:
      InstrumentationTimer(const char* name)
         : m_name(name)
         , m_stopped(false)
         , m_startTimepoint(std::chrono::high_resolution_clock::now())
      {
      }

      ~InstrumentationTimer()
      {
         if (!m_stopped)
            stop();
      }

      void stop()
      {
         using namespace std::chrono;
         auto end_timepoint = high_resolution_clock::now();

         auto start = time_point_cast<microseconds>(m_startTimepoint).time_since_epoch().count();
         auto end = time_point_cast<microseconds>(end_timepoint).time_since_epoch().count();

         auto thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
         Instrumentor::get().writeProfile({m_name, start, end, thread_id});

         m_stopped = true;
      }

   private:
      const char* m_name;
      std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;
      bool m_stopped;
   };
}

#ifdef NT_PROFILE
   #define NT_PROFILE_BEGIN_SESSION(name, filepath) ::Neat::Instrumentor::get().beginSession(name, filepath)
   #define NT_PROFILE_END_SESSION() ::Neat::Instrumentor::get().endSession()
   #define NT_PROFILE_FUNCTION() NT_PROFILE_SCOPE(__FUNCSIG__)
   #define NT_PROFILE_SCOPE(name) ::Neat::InstrumentationTimer timer##__LINE__(name)
#else
   #define NT_PROFILE_BEGIN_SESSION(name, filepath)
   #define NT_PROFILE_END_SESSION()
   #define NT_PROFILE_FUNCTION()
   #define NT_PROFILE_SCOPE(name)
#endif