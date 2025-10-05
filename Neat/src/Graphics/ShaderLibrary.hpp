#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "ShaderProgram.hpp"

#include "Core/Types.hpp"
#include "Math/Matrix.hpp"
#include "Math/Vector.hpp"

namespace Neat {
class ShaderLibrary {
 public:
  void add(const Ref<ShaderProgram> &shader);
  void add(const std::string &name, const Ref<ShaderProgram> &shader);
  Ref<ShaderProgram> load(const std::string &filepath);
  Ref<ShaderProgram> load(const std::string &name, const std::string &filepath);
  Ref<ShaderProgram> get(const std::string &name);

  bool exists(const std::string &name) const;

 private:
  std::unordered_map<std::string, Ref<ShaderProgram>> m_shaders;
};
}  // namespace Neat