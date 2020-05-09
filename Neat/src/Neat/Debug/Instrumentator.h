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
      SizeType theadID;
   };

   struct InstrumentationSession
   {
      std::string name;
   };

   class Instrumentor
   {
   private:
      InstrumentationSession* currentSession;
      std::ofstream outputStream;
      Int profileCount;
      std::mutex writingMutex;

   public:
      Instrumentor()
         : currentSession(nullptr), profileCount(0)
      {
      }

      void beginSession(const std::string& name, const std::string& filepath = "results.json")
      {
         this->outputStream.open(filepath);
         writeHeader();
         this->currentSession = new InstrumentationSession{name};
      }

      void endSession()
      {
         writeFooter();
         this->outputStream.close();
         delete this->currentSession;
         this->currentSession = nullptr;
         this->profileCount = 0;
      }

      void writeProfile(const ProfileResult& result)
      {
         writingMutex.lock();
         if (this->profileCount++ > 0)
            this->outputStream << ",";

         std::string name = result.name;
         std::replace(name.begin(), name.end(), '"', '\'');

         this->outputStream << "{";
         this->outputStream << "\"cat\":\"function\",";
         this->outputStream << "\"dur\":" << (result.end - result.start) << ",";
         this->outputStream << "\"name\":\"" << name << "\",";
         this->outputStream << "\"ph\":\"X\",";
         this->outputStream << "\"pid\":0,";
         this->outputStream << "\"tid\":" << result.theadID << ",";
         this->outputStream << "\"ts\":" << result.start;
         this->outputStream << "}";

         this->outputStream.flush();
         writingMutex.unlock();
      }

      void writeHeader()
      {
         this->outputStream << "{\"otherData\": {},\"traceEvents\":[";
         this->outputStream.flush();
      }

      void writeFooter()
      {
         this->outputStream << "]}";
         this->outputStream.flush();
      }

      static Instrumentor& get()
      {
         static Instrumentor instance;
         return instance;
      }
   };

   class InstrumentationTimer
   {
   public:
      InstrumentationTimer(const Char* name)
         : name(name)
         , stopped(false)
         , startTimepoint(std::chrono::high_resolution_clock::now())
      {
      }

      ~InstrumentationTimer()
      {
         if (!this->stopped)
            this->stop();
      }

      void stop()
      {
         using namespace std::chrono;
         auto end_timepoint = high_resolution_clock::now();

         auto start = time_point_cast<microseconds>(startTimepoint).time_since_epoch().count();
         auto end = time_point_cast<microseconds>(end_timepoint).time_since_epoch().count();

         auto thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
         Instrumentor::get().writeProfile({this->name, start, end, thread_id});

         this->stopped = true;
      }
   private:
      const Char* name;
      std::chrono::time_point<std::chrono::high_resolution_clock> startTimepoint;
      Bool stopped;
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