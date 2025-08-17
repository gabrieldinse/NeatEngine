#pragma once

#include "Neat/Graphics/FrameBuffer.hpp"

namespace Neat {
class OpenGLFrameBuffer : public FrameBuffer {
 public:
  OpenGLFrameBuffer(const FrameBufferSpecification& spec);
  virtual ~OpenGLFrameBuffer();

  virtual void bind() override;
  virtual void unbind() override;

  virtual const FrameBufferSpecification& getSpecification() const override {
    return m_specification;
  }

  virtual UInt32 getColorAttachmentID() const override {
    return m_colorAttachmentTextureID;
  }

  virtual void resize(UInt32 width, UInt32 height) override;

 private:
  void recreate();

 private:
  UInt32 m_id = 0;
  UInt32 m_colorAttachmentTextureID = 0;
  UInt32 m_depthAttachmentTextureID = 0;
  FrameBufferSpecification m_specification;
};
}  // namespace Neat