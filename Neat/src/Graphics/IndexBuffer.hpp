#pragma once

#include <memory>

#include "Core/Types.hpp"

namespace Neat {
class IndexBuffer {
 public:
  virtual ~IndexBuffer() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual UInt32 getCount() const = 0;
  static Ref<IndexBuffer> create(UInt32 *indices, UInt32 count);
};
}  // namespace Neat