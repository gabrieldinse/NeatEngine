#pragma once

#include <memory>
#include <string>

#include "Neat/Core/Types.hpp"
#include "Neat/Math/Vector.hpp"
#include "Neat/Graphics/Texture.hpp"

namespace Neat {

class Texture2D : public Texture {
 public:
  static std::shared_ptr<Texture2D> create(Int32 width, Int32 height);
  static std::shared_ptr<Texture2D> create(const std::string &filepath);
};
}  // namespace Neat