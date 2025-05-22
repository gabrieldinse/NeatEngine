#pragma once

#include "Neat/Core/Log.hpp"


#ifdef NT_PLATFORM_LINUX

extern std::unique_ptr<Neat::Application> Neat::createApplication();

int main(int argc, char* argv[])
{
   Neat::Log::init();

   auto application = Neat::createApplication();
   application->run();
}

#endif