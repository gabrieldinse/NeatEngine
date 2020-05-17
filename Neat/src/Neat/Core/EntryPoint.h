#pragma once

#include "Neat/Core/Log.h"


#ifdef NT_PLATFORM_WINDOWS

extern std::unique_ptr<Neat::Application> Neat::createApplication();

int main(int argc, char* argv[])
{
   Neat::Log::init();

   NT_PROFILE_BEGIN_SESSION("Startup", "Dingal_profile_startup.json");
   auto application = Neat::createApplication();
   NT_PROFILE_END_SESSION();

   NT_PROFILE_BEGIN_SESSION("Runtime", "Dingal_profile_runtime.json");
   application->run();
   NT_PROFILE_END_SESSION();

   NT_PROFILE_BEGIN_SESSION("Shutdown", "Dingal_profile_shutdown.json");
   application.reset(nullptr);
   NT_PROFILE_END_SESSION();
}

#endif