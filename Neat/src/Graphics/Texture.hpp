#pragma once

#include "Core/Types.hpp"
#include "Math/Types/Vector2.hpp"

namespace Neat {
class Texture {
 public:
  virtual ~Texture() = default;

  virtual Int32 getWidth() const = 0;
  virtual Int32 getHeight() const = 0;
  virtual UInt32 getRendererID() const = 0;
  virtual const Vector2F *getCoordinates() const = 0;
  virtual const std::string &getFilepath() const = 0;
  virtual bool isLoaded() const = 0;

  virtual void setData(void *data, UInt32 size) = 0;

  virtual void bind(UInt32 slot) const = 0;
  virtual bool operator==(const Texture &other) const = 0;
};
}  // namespace Neat