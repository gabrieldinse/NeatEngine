#pragma once

#include "Neat/Graphics/Buffers.hpp"

namespace Neat {

// ---------------------------------------------------------------------- //
// OpenGLVertexBuffer ---------------------------------------------------------
// //
// ---------------------------------------------------------------------- //
class OpenGLVertexBuffer : public VertexBuffer {
 public:
  OpenGLVertexBuffer(UInt32 size);
  OpenGLVertexBuffer(float *vertices, UInt32 size);
  virtual ~OpenGLVertexBuffer();

  virtual void bind() const override;
  virtual void unbind() const override;

  virtual UInt32 getId() const override { return m_id; }

  virtual const BufferLayout &getLayout() const override { return m_layout; }
  virtual void setLayout(const BufferLayout &layout) override;

  virtual void setData(const void *data, UInt32 size) override;

 private:
  UInt32 m_id = 0;
  BufferLayout m_layout;
};

// ---------------------------------------------------------------------- //
// OpenGLIndexBuffer ----------------------------------------------------------
// //
// ---------------------------------------------------------------------- //
class OpenGLIndexBuffer : public IndexBuffer {
 public:
  OpenGLIndexBuffer(UInt32 *indices, UInt32 count);
  virtual ~OpenGLIndexBuffer();

  virtual void bind() const override;
  virtual void unbind() const override;

  virtual UInt32 getCount() const override { return m_count; }

 private:
  UInt32 m_id = 0;
  UInt32 m_count;
};
}  // namespace Neat