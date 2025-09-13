#include "NeatPCH.hpp"

#include "OpenGLFrameBuffer.hpp"

#include <glad/glad.h>

namespace Neat {
OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec)
    : m_specification(spec) {
  NT_PROFILE_FUNCTION();
  recreate();
}

OpenGLFrameBuffer::~OpenGLFrameBuffer() {
  NT_PROFILE_FUNCTION();
  glDeleteBuffers(1, &m_id);
  glDeleteTextures(1, &m_colorAttachmentTextureID);
  glDeleteTextures(1, &m_depthAttachmentTextureID);
}

void OpenGLFrameBuffer::bind() {
  NT_PROFILE_FUNCTION();
  glBindFramebuffer(GL_FRAMEBUFFER, m_id);
  glViewport(0, 0, m_specification.width, m_specification.height);
}

void OpenGLFrameBuffer::unbind() {
  NT_PROFILE_FUNCTION();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFrameBuffer::recreate() {
  NT_PROFILE_FUNCTION();

  if (m_id != 0) {
    glDeleteFramebuffers(1, &m_id);
    m_id = 0;
  }

  if (m_colorAttachmentTextureID != 0) {
    glDeleteTextures(1, &m_colorAttachmentTextureID);
    m_colorAttachmentTextureID = 0;
  }

  if (m_depthAttachmentTextureID != 0) {
    glDeleteTextures(1, &m_depthAttachmentTextureID);
    m_depthAttachmentTextureID = 0;
  }

  glCreateFramebuffers(1, &m_id);
  glBindFramebuffer(GL_FRAMEBUFFER, m_id);

  glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachmentTextureID);
  glBindTexture(GL_TEXTURE_2D, m_colorAttachmentTextureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_specification.width,
               m_specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         m_colorAttachmentTextureID, 0);

  glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachmentTextureID);
  glBindTexture(GL_TEXTURE_2D, m_depthAttachmentTextureID);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_specification.width,
                 m_specification.height);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                         GL_TEXTURE_2D, m_depthAttachmentTextureID, 0);

  NT_CORE_ASSERT(
      glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
      "Framebuffer is not complete!");

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFrameBuffer::resize(UInt32 width, UInt32 height) {
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
}  // namespace Neat