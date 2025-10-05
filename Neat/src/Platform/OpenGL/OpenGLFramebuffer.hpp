#pragma once

#include "Graphics/Framebuffer.hpp"

namespace Neat {
class OpenGLFramebuffer : public Framebuffer {
 public:
  OpenGLFramebuffer(const FramebufferSpecification& spec);
  virtual ~OpenGLFramebuffer();

  virtual void bind() override;
  virtual void unbind() override;

  virtual const FramebufferSpecification& getSpecification() const override {
    return m_specification;
  }

  virtual UInt32 getColorAttachmentID(UInt32 index = 0) const override;

  virtual void resize(UInt32 width, UInt32 height) override;
  virtual UInt32 getUInt32Pixel(UInt32 index, Vector2UI position) override;
  virtual void clearUInt32ColorAttachment(UInt32 index, UInt32 value) override;

 private:
  void recreate();
  void destroyFramebuffer();
  void createFramebuffer();
  void createColorAttachmentTextures();
  std::vector<UInt32> createTextures(UInt32 count);
  void bindTexture(UInt32 id);
  void attachColorTexture(UInt32 index);
  void createDepthAttachmentTexture();
  void attachDepthTexture();
  void checkCompleteness();
  void drawBuffers();
  bool isMultisampled() const { return m_specification.samples > 1; }
  UInt32 getTextureTarget() const;

 private:
  UInt32 m_id = 0;
  FramebufferSpecification m_specification;
  std::vector<UInt32> m_colorAttachmentIDs;
  UInt32 m_depthAttachmentID = 0;
};
}  // namespace Neat