#pragma once

#include "Graphics/VertexBuffer.hpp"

namespace Neat {
class OpenGLVertexBuffer : public VertexBuffer {
 public:
  OpenGLVertexBuffer(UInt32 size);
  OpenGLVertexBuffer(float *vertices, UInt32 size);
  virtual ~OpenGLVertexBuffer();

  virtual void bind() const override;
  virtual void unbind() const override;

  virtual UInt32 getId() const override { return m_id; }

  virtual const VertexBufferLayout &getLayout() const override {
    return m_layout;
  }
  virtual void setLayout(const VertexBufferLayout &layout) override;

  virtual void setData(const void *data, UInt32 size) override;

 private:
  UInt32 m_id = 0;
  VertexBufferLayout m_layout;
};
}  // namespace Neat