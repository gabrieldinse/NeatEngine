#pragma once

#include "Neat/Core/Log.hpp"
#include "Neat/Core/Types.hpp"
#include "Neat/Debug/Debug.hpp"

#ifdef NT_PLATFORM_LINUX

extern Neat::Scope<Neat::Application> Neat::createApplication();

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  Neat::Log::initialize();

  NT_PROFILE_BEGIN_SESSION("CreateApp", "Neat-Profile.json");
  Neat::Scope<Neat::Application> app = Neat::createApplication();
  NT_PROFILE_END_SESSION();

  NT_PROFILE_BEGIN_SESSION("Runtime", "Neat-Profile.json");
  // app->run();
  NT_PROFILE_END_SESSION();
}

#endif