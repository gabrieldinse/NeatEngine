#include "Neat/Core/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace Neat
{
   std::shared_ptr<spdlog::logger> Log::clientLogger;
   std::shared_ptr<spdlog::logger> Log::coreLogger;

   void Log::init(const Char* pattern)
   {
      spdlog::set_pattern(pattern);
      Log::coreLogger = spdlog::stdout_color_mt("DINGAL");
      Log::coreLogger->set_level(spdlog::level::trace);
      Log::clientLogger = spdlog::stdout_color_mt("APP");
      Log::clientLogger->set_level(spdlog::level::trace);
   }
}
