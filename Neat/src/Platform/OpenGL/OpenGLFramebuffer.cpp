#include "NeatPCH.hpp"

#include "OpenGLFramebuffer.hpp"
#include "OpenGLUtils.hpp"

#include <glad/glad.h>

namespace Neat {
OpenGLFramebuffer::OpenGLFramebuffer(
    const FramebufferSpecification& specification)
    : m_specification(specification) {
  NT_PROFILE_FUNCTION();
  recreate();
}

OpenGLFramebuffer::~OpenGLFramebuffer() {
  NT_PROFILE_FUNCTION();
  destroyFramebuffer();
}

void OpenGLFramebuffer::bind() {
  NT_PROFILE_FUNCTION();
  glBindFramebuffer(GL_FRAMEBUFFER, m_id);
  glViewport(0, 0, m_specification.width, m_specification.height);
}

UInt32 OpenGLFramebuffer::getColorAttachmentID(UInt32 index) const {
  NT_PROFILE_FUNCTION();

  NT_CORE_ASSERT(index < m_colorAttachmentIDs.size(),
                 "Color attachment index out of bounds.");

  return m_colorAttachmentIDs[index];
}

void OpenGLFramebuffer::unbind() {
  NT_PROFILE_FUNCTION();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::resize(UInt32 width, UInt32 height) {
  NT_PROFILE_FUNCTION();

  if (width == 0 || height == 0 || width > 8192 || height > 8192) {
    NT_CORE_WARN(
        "Attempted to resize framebuffer to ({}, {}). Framebuffer resize "
        "aborted.",
        width, height);
    return;
  }

  m_specification.width = width;
  m_specification.height = height;
  recreate();
}

void OpenGLFramebuffer::recreate() {
  NT_PROFILE_FUNCTION();
  destroyFramebuffer();
  createFramebuffer();
  createColorAttachmentTextures();
  createDepthAttachmentTexture();
  drawBuffers();
  checkCompleteness();
}

UInt32 OpenGLFramebuffer::getUInt32Pixel(UInt32 index, Vector2UI position) {
  NT_PROFILE_FUNCTION();

  NT_CORE_ASSERT(index < m_colorAttachmentIDs.size(),
                 "Color attachment index out of bounds.");

  glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
  UInt32 pixelData = 0;
  glReadPixels(position.x(), position.y(), 1, 1, GL_RED_INTEGER,
               GL_UNSIGNED_INT, &pixelData);
  return pixelData;
}

void OpenGLFramebuffer::clearUInt32ColorAttachment(UInt32 index, UInt32 value) {
  NT_PROFILE_FUNCTION();

  NT_CORE_ASSERT(index < m_colorAttachmentIDs.size(),
                 "Color attachment index out of bounds.");

  auto format = m_specification.colorAttachments.attachments[index].format;
  glClearTexImage(m_colorAttachmentIDs[index], 0,
                  OpenGL::getFramebufferColorFormat(format), GL_UNSIGNED_INT,
                  &value);
}

void OpenGLFramebuffer::destroyFramebuffer() {
  NT_PROFILE_FUNCTION();

  if (m_id != 0) {
    glDeleteFramebuffers(1, &m_id);
    m_id = 0;
  }

  if (not m_colorAttachmentIDs.empty()) {
    glDeleteTextures(m_colorAttachmentIDs.size(), m_colorAttachmentIDs.data());
    m_colorAttachmentIDs.clear();
  }

  if (m_depthAttachmentID != 0) {
    glDeleteTextures(1, &m_depthAttachmentID);
    m_depthAttachmentID = 0;
  }
}

void OpenGLFramebuffer::createFramebuffer() {
  NT_PROFILE_FUNCTION();

  glCreateFramebuffers(1, &m_id);
  glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void OpenGLFramebuffer::createColorAttachmentTextures() {
  NT_PROFILE_FUNCTION();

  m_colorAttachmentIDs =
      createTextures(m_specification.colorAttachments.attachments.size());
  for (UInt32 i = 0; i < m_colorAttachmentIDs.size(); ++i) {
    bindTexture(m_colorAttachmentIDs[i]);
    attachColorTexture(i);
  }
}

void OpenGLFramebuffer::attachColorTexture(UInt32 index) {
  NT_PROFILE_FUNCTION();

  auto format = m_specification.colorAttachments.attachments[index].format;
  if (isMultisampled()) {
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_specification.samples,
                            OpenGL::getFramebufferColorInternalFormat(format),
                            m_specification.width, m_specification.height,
                            GL_FALSE);
  } else {
    glTexImage2D(
        GL_TEXTURE_2D, 0, OpenGL::getFramebufferColorInternalFormat(format),
        m_specification.width, m_specification.height, 0,
        OpenGL::getFramebufferColorFormat(format), GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index,
                         getTextureTarget(), m_colorAttachmentIDs[index], 0);
}

std::vector<UInt32> OpenGLFramebuffer::createTextures(UInt32 count) {
  NT_PROFILE_FUNCTION();

  std::vector<UInt32> attachmentIDs;
  attachmentIDs.resize(count);
  glCreateTextures(GL_TEXTURE_2D, attachmentIDs.size(), attachmentIDs.data());
  return attachmentIDs;
}

void OpenGLFramebuffer::bindTexture(UInt32 id) {
  NT_PROFILE_FUNCTION();

  glBindTexture(OpenGL::getTextureTarget(m_specification.samples > 1), id);
}

void OpenGLFramebuffer::createDepthAttachmentTexture() {
  NT_PROFILE_FUNCTION();

  if (m_specification.depthAttachment.format != FramebufferDepthFormat::None) {
    m_depthAttachmentID = createTextures(1)[0];
    bindTexture(m_depthAttachmentID);
    attachDepthTexture();
  }
}

void OpenGLFramebuffer::attachDepthTexture() {
  NT_PROFILE_FUNCTION();
  auto format = m_specification.depthAttachment.format;
  if (isMultisampled()) {
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_specification.samples,
                            OpenGL::getFramebufferDepthFormat(format),
                            m_specification.width, m_specification.height,
                            GL_FALSE);
  } else {
    glTexStorage2D(GL_TEXTURE_2D, 1, OpenGL::getFramebufferDepthFormat(format),
                   m_specification.width, m_specification.height);
  }

  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         OpenGL::getFramebufferDepthAttachmentType(format),
                         getTextureTarget(), m_depthAttachmentID, 0);
}

void OpenGLFramebuffer::drawBuffers() {
  NT_PROFILE_FUNCTION();

  if (m_colorAttachmentIDs.size() > 1) {
    NT_CORE_ASSERT(m_colorAttachmentIDs.size() <= 2,
                   "Only up to 2 color attachments are supported.");
    constexpr UInt32 buffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(m_colorAttachmentIDs.size(), buffers);
  } else if (m_colorAttachmentIDs.empty()) {
    glDrawBuffer(GL_NONE);
  }
}

void OpenGLFramebuffer::checkCompleteness() {
  NT_PROFILE_FUNCTION();

  NT_CORE_ASSERT(
      glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
      "Framebuffer is not complete!");

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

UInt32 OpenGLFramebuffer::getTextureTarget() const {
  return isMultisampled() ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}
}  // namespace Neat