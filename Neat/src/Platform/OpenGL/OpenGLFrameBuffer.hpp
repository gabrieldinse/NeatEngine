#pragma once

#include "Neat/Graphics/FrameBuffer.hpp"

namespace Neat {
class OpenGLFrameBuffer : public FrameBuffer {
 public:
  OpenGLFrameBuffer(const FrameBufferSpecification& spec);
  virtual ~OpenGLFrameBuffer();

  virtual UInt32 getColorAttachmentID() const override {
    return m_colorAttachmentTextureID;
  }
  virtual const FrameBufferSpecification& getSpecification() const override {
    return m_specification;
  }
  virtual void bind() override;
  virtual void unbind() override;

 private:
  void recreate();

 private:
  UInt32 m_id;
  UInt32 m_colorAttachmentTextureID;
  UInt32 m_depthAttachmentTextureID;
  FrameBufferSpecification m_specification;
};
}  // namespace Neat