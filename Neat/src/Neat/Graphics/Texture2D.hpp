#pragma once

#include <memory>
#include <string>

#include "Neat/Core/Types.hpp"
#include "Neat/Math/Vector.hpp"
#include "Neat/Graphics/Texture.hpp"

namespace Neat {

class Texture2D : public Texture {
 public:
  static Ref<Texture2D> create(Int32 width, Int32 height);
  static Ref<Texture2D> create(const std::string &filepath);
};
}  // namespace Neat