#pragma once

#include "Neat/Core/Types.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
class Texture {
 public:
  virtual ~Texture() = default;

  virtual Int32 getWidth() const = 0;
  virtual Int32 getHeight() const = 0;
  virtual UInt32 getRendererID() const = 0;
  virtual const Vector2F *getCoordinates() const = 0;

  virtual void setData(void *data, UInt32 size) = 0;

  virtual void bind(UInt32 slot) const = 0;
  virtual bool operator==(const Texture &other) const = 0;
};
}  // namespace Neat