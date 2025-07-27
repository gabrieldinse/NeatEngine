#pragma once

#include "Neat/Core/Log.hpp"
#include "Neat/Core/Types.hpp"
#include "Neat/Debug/Debug.hpp"

#ifdef NT_PLATFORM_LINUX

extern Neat::Scope<Neat::Application> Neat::createApplication();

int main(int argc, char *argv[]) {
  Neat::Log::init();

  NT_PROFILE_BEGIN_SESSION("Runtime", "Neat-Profile.json");
  Neat::createApplication()->run();
  NT_PROFILE_END_SESSION();
}

#endif