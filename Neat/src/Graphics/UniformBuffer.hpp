#pragma once

#include "Core/Types.hpp"
#include "Math/Matrix.hpp"

namespace Neat {
class UniformBuffer {
 public:
  virtual ~UniformBuffer() = default;

  virtual UInt32 getSize() const = 0;
  virtual void setData(const Matrix4F &matrix, UInt32 offset = 0) = 0;
  virtual void setData(const void *data, UInt32 size, UInt32 offset = 0) = 0;

  static Scope<UniformBuffer> create(UInt32 size, UInt32 binding);
};
}  // namespace Neat