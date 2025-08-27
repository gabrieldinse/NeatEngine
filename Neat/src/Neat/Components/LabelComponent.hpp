#pragma once

#include <string>

namespace Neat {
struct LabelComponent {
  std::string label{"Unnamed Entity"};

  operator std::string() const { return label; }
  const char *getRawLabel() const { return label.c_str(); }
};
}  // namespace Neat