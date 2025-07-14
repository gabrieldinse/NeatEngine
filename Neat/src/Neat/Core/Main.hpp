#pragma once

#include "Neat/Core/Log.hpp"
#include "Neat/Core/Types.hpp"

#ifdef NT_PLATFORM_LINUX

extern Neat::Scope<Neat::Application> Neat::createApplication();

int main(int argc, char *argv[]) {
  Neat::Log::init();
  Neat::createApplication()->run();
}

#endif