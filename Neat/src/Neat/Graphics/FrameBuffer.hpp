#pragma once

#include "Neat/Core/Types.hpp"

namespace Neat {
struct FrameBufferSpecification {
  UInt32 width;
  UInt32 height;
  UInt32 samples = 1;
};

class FrameBuffer {
 public:
  static Ref<FrameBuffer> create(const FrameBufferSpecification& spec);

  virtual UInt32 getColorAttachmentID() const = 0;
  virtual void bind() = 0;
  virtual void unbind() = 0;
  virtual const FrameBufferSpecification& getSpecification() const = 0;
};
}  // namespace Neat