#pragma once

#include "Instrumentor.hpp"
#include "InstrumentationTimer.hpp"
#include "Utils.hpp"

/*
 * This profiling tools are meant to be used with the visual analyzer
 * chrome://tracing. Just drag and drop the resulting .json file into the
 * screen.
 */

#define NT_PROFILE 0
#if NT_PROFILE
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || \
    (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define NT_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define NT_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
#define NT_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || \
    (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define NT_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define NT_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define NT_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define NT_FUNC_SIG __func__
#else
#define NT_FUNC_SIG "NT_FUNC_SIG unknown!"
#endif

#define NT_PROFILE_BEGIN_SESSION(name, filepath) \
  ::Neat::Instrumentor::get().beginSession(name, filepath)
#define NT_PROFILE_END_SESSION() ::Neat::Instrumentor::get().endSession()
#define NT_PROFILE_SCOPE_LINE2(name, line)           \
  constexpr auto fixedName##line =                   \
      ::Neat::cleanupOutputString(name, "__cdecl "); \
  ::Neat::InstrumentationTimer timer##line(fixedName##line.data)
#define NT_PROFILE_SCOPE_LINE(name, line) NT_PROFILE_SCOPE_LINE2(name, line)
#define NT_PROFILE_SCOPE(name) NT_PROFILE_SCOPE_LINE(name, __LINE__)
#define NT_PROFILE_FUNCTION() NT_PROFILE_SCOPE(NT_FUNC_SIG)
#else
#define NT_PROFILE_BEGIN_SESSION(name, filepath)
#define NT_PROFILE_END_SESSION()
#define NT_PROFILE_SCOPE(name)
#define NT_PROFILE_FUNCTION()
#endif