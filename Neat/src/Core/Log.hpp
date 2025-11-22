#pragma once

#include "Types.hpp"

#include <spdlog/spdlog.h>

#undef near
#undef far

namespace Neat {
class Log {
 public:
  Log() = default;
  ~Log() = default;
  static void initialize(const char *pattern = "%^[%T] %n: %v%$");

  inline static Ref<spdlog::logger> &getCoreLogger() {
    return Log::s_coreLogger;
  }

  inline static Ref<spdlog::logger> &getClientLogger() {
    return Log::s_clientLogger;
  }

 private:
  static Ref<spdlog::logger> s_coreLogger;
  static Ref<spdlog::logger> s_clientLogger;
};
}  // namespace Neat

// Core log macros
#ifdef NT_DEBUG
#define NT_CORE_ERROR(...) ::Neat::Log::getCoreLogger()->error(__VA_ARGS__)
#define NT_CORE_WARN(...) ::Neat::Log::getCoreLogger()->warn(__VA_ARGS__)
#define NT_CORE_INFO(...) ::Neat::Log::getCoreLogger()->info(__VA_ARGS__)
#define NT_CORE_TRACE(...) ::Neat::Log::getCoreLogger()->trace(__VA_ARGS__)
#define NT_CORE_FATAL(...) ::Neat::Log::getCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define NT_ERROR(...) ::Neat::Log::getClientLogger()->error(__VA_ARGS__)
#define NT_WARN(...) ::Neat::Log::getClientLogger()->warn(__VA_ARGS__)
#define NT_INFO(...) ::Neat::Log::getClientLogger()->info(__VA_ARGS__)
#define NT_TRACE(...) ::Neat::Log::getClientLogger()->trace(__VA_ARGS__)
#define NT_FATAL(...) ::Neat::Log::getClientLogger()->fatal(__VA_ARGS__)

#else
#define NT_CORE_ERROR
#define NT_CORE_WARN
#define NT_CORE_INFO
#define NT_CORE_TRACE
#define NT_CORE_FATAL
#define NT_ERROR
#define NT_WARN
#define NT_INFO
#define NT_TRACE
#define NT_FATAL

#endif