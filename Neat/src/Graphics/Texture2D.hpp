#pragma once

#include <memory>
#include <string>

#include "Texture.hpp"

#include "Core/Types.hpp"

namespace Neat {
enum class Texture2DFilter {
  Nearest,
  Linear,
  NearestMipmapNearest,
  NearestMipmapLinear,
  LinearMipmapLinear,
  LinearMipmapNearest,
};

enum class Texture2DWrapping {
  Repeat,
  MirroredRepeat,
  ClampToEdge,
  ClampToBorder,
};

class Texture2D : public Texture {
 public:
  static Ref<Texture2D> create(Int32 width, Int32 height);
  static Ref<Texture2D> create(const std::string &filepath);
  virtual void setMinification(Texture2DFilter minificationFilter) = 0;
  virtual void setMagnification(Texture2DFilter magnificationFilter) = 0;
  virtual void setWrapS(Texture2DWrapping wrapS) = 0;
  virtual void setWrapT(Texture2DWrapping wrapT) = 0;
};
}  // namespace Neat