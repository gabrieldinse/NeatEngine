#pragma once

#include "Neat/Graphics/IndexBuffer.hpp"

namespace Neat {
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