#include "NeatPCH.hpp"

#include "Log.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Neat {
Ref<spdlog::logger> Log::s_clientLogger;
Ref<spdlog::logger> Log::s_coreLogger;

void Log::initialize(const char *pattern) {
  spdlog::set_pattern(pattern);
  Log::s_coreLogger = spdlog::stdout_color_mt("NEAT");
  Log::s_coreLogger->set_level(spdlog::level::trace);
  Log::s_clientLogger = spdlog::stdout_color_mt("APP");
  Log::s_clientLogger->set_level(spdlog::level::trace);
}
}  // namespace Neat
