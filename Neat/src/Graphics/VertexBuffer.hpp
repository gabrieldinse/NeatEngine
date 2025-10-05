#pragma once

#include <memory>

#include "VertexBufferLayout.hpp"

#include "Core/Types.hpp"

namespace Neat {
class VertexBuffer {
 public:
  virtual ~VertexBuffer() = default;

  virtual void bind() const = 0;
  virtual void unbind() const = 0;

  virtual UInt32 getId() const = 0;

  virtual const VertexBufferLayout &getLayout() const = 0;
  virtual void setLayout(const VertexBufferLayout &layout) = 0;

  virtual void setData(const void *data, UInt32 size) = 0;

  static Ref<VertexBuffer> create(UInt32 size);
  static Ref<VertexBuffer> create(float *vertices, UInt32 size);
};
}  // namespace Neat