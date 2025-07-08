#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Neat/Core/Types.hpp"
#include "Neat/Math/Matrix.hpp"
#include "Neat/Math/Vector.hpp"
#include "Neat/Graphics/ShaderProgram.hpp"

namespace Neat {
class ShaderLibrary {
 public:
  void add(const std::shared_ptr<ShaderProgram> &shader);
  void add(const std::string &name,
           const std::shared_ptr<ShaderProgram> &shader);
  std::shared_ptr<ShaderProgram> load(const std::string &filepath);
  std::shared_ptr<ShaderProgram> load(const std::string &name,
                                      const std::string &filepath);
  std::shared_ptr<ShaderProgram> get(const std::string &name);

  bool exists(const std::string &name) const;

 private:
  std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> m_shaders;
};
}  // namespace Neat