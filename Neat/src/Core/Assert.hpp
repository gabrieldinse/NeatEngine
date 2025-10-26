#pragma once

#include <filesystem>

#include "Log.hpp"
#include "PlatformDetection.hpp"

#define NT_EXPAND_MACRO(x) x
#define NT_STRINGIFY_MACRO(x) #x

// Debugging
#ifdef NT_DEBUG
#define NT_ENABLE_ASSERTS
#endif

#ifdef NT_DEBUG
#if defined(NT_PLATFORM_WINDOWS)
#define NT_DEBUGBREAK() __debugbreak()
#elif defined(NT_PLATFORM_LINUX)
#include <signal.h>
#define NT_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define NT_ENABLE_ASSERTS
#else
#define NT_DEBUGBREAK()
#endif

#ifdef NT_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and
// "NO_MSG" and provide support for custom formatting by concatenating the
// formatting string instead of having the format inside the default message
#define NT_INTERNAL_ASSERT_IMPL(type, check, msg, ...) \
  {                                                    \
    if (!(check)) {                                    \
      NT##type##ERROR(msg, __VA_ARGS__);               \
      NT_DEBUGBREAK();                                 \
    }                                                  \
  }
#define NT_INTERNAL_ASSERT_WITH_MSG(type, check, ...) \
  NT_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define NT_INTERNAL_ASSERT_NO_MSG(type, check)                                 \
  NT_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}",    \
                          NT_STRINGIFY_MACRO(check),                           \
                          std::filesystem::path(__FILE__).filename().string(), \
                          __LINE__)

#define NT_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define NT_INTERNAL_ASSERT_GET_MACRO(...)            \
  NT_EXPAND_MACRO(NT_INTERNAL_ASSERT_GET_MACRO_NAME( \
      __VA_ARGS__, NT_INTERNAL_ASSERT_WITH_MSG, NT_INTERNAL_ASSERT_NO_MSG))

// Currently accepts at least the condition and One additional parameter (the
// message) being optional
#define NT_ASSERT(...) \
  NT_EXPAND_MACRO(NT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#define NT_CORE_ASSERT(...) \
  NT_EXPAND_MACRO(          \
      NT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
#define NT_ASSERT(...)
#define NT_CORE_ASSERT(...)
#endif
