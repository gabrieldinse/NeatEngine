#pragma once

#include <vector>
#include <string>

#include "Neat/Core/Types.hpp"

namespace Neat {
struct ApplicationCommandLineArguments {
  ApplicationCommandLineArguments() = default;
  ApplicationCommandLineArguments(UInt32 count, char **args);

  std::vector<std::string> arguments;

  const std::string &operator[](UInt32 index) const { return arguments[index]; }

  UInt32 count() const { return static_cast<UInt32>(arguments.size()); }
};
}  // namespace Neat