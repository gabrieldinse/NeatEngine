#pragma once

#include <initializer_list>

#include "Core/Types.hpp"
#include "Math/Types/Vector2.hpp"

namespace Neat {
enum class FramebufferColorFormat {
  None = 0,
  RGBA8 = 1,
  RedUInt32 = 2,
  OneUInt32 = RedUInt32,
};

enum class FramebufferDepthFormat {
  None = 0,
  Depth24Stencil8 = 1,
};

struct FramebufferColorSpecification {
  FramebufferColorSpecification() = default;
  FramebufferColorSpecification(FramebufferColorFormat format)
      : format(format) {}
  FramebufferColorFormat format = FramebufferColorFormat::None;
};

struct FramebufferColorSpecificationList {
  FramebufferColorSpecificationList() = default;
  FramebufferColorSpecificationList(
      std::initializer_list<FramebufferColorSpecification> list)
      : attachments(list) {}
  std::vector<FramebufferColorSpecification> attachments;
};

struct FramebufferDepthSpecification {
  FramebufferDepthSpecification() = default;
  FramebufferDepthSpecification(FramebufferDepthFormat format)
      : format(format) {}
  FramebufferDepthFormat format = FramebufferDepthFormat::None;
};

struct FramebufferSpecification {
  UInt32 width;
  UInt32 height;
  FramebufferColorSpecificationList colorAttachments;
  FramebufferDepthSpecification depthAttachment;
  UInt32 samples = 1;
};

class Framebuffer {
 public:
  virtual ~Framebuffer() = default;
  static Ref<Framebuffer> create(const FramebufferSpecification& spec);

  virtual UInt32 getColorAttachmentID(UInt32 index = 0) const = 0;
  virtual void bind() = 0;
  virtual void unbind() = 0;
  virtual void resize(UInt32 width, UInt32 height) = 0;
  virtual UInt32 getUInt32Pixel(UInt32 index, Vector2UI position) = 0;
  virtual void clearUInt32ColorAttachment(UInt32 index, UInt32 value) = 0;
  virtual const FramebufferSpecification& getSpecification() const = 0;
};
}  // namespace Neat