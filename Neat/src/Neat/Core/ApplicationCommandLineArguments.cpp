#include "NeatPCH.hpp"

#include "ApplicationCommandLineArguments.hpp"

namespace Neat {
ApplicationCommandLineArguments::ApplicationCommandLineArguments(UInt32 count,
                                                                 char **args) {
  NT_PROFILE_FUNCTION();
  for (UInt32 i = 0; i < count; ++i) {
    this->arguments.emplace_back(args[i]);
  }
}
}  // namespace Neat