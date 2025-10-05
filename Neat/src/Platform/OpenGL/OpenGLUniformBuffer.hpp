#pragma once

#include "Graphics/UniformBuffer.hpp"

namespace Neat {
class OpenGLUniformBuffer : public UniformBuffer {
 public:
  OpenGLUniformBuffer(UInt32 size, UInt32 binding);
  virtual ~OpenGLUniformBuffer();

  virtual UInt32 getSize() const override { return m_size; }
  virtual void setData(const Matrix4F &matrix, UInt32 offset = 0) override;
  virtual void setData(const void *data, UInt32 size,
                       UInt32 offset = 0) override;

 private:
  UInt32 m_id = 0;
  UInt32 m_size;
};
}  // namespace Neat