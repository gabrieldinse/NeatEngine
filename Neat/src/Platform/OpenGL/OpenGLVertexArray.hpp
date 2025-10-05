#pragma once

#include "Core/Types.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/VertexArray.hpp"

namespace Neat {
class OpenGLVertexArray : public VertexArray {
 public:
  OpenGLVertexArray();
  virtual ~OpenGLVertexArray();
  virtual void bind() const override;
  virtual void unbind() const override;

  virtual void addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
  virtual void setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;

  virtual const std::vector<Ref<VertexBuffer>> &getVertexBuffers()
      const override {
    return m_vertexBuffers;
  }

  virtual const Ref<IndexBuffer> &getIndexBuffer() const override {
    return m_indexBuffer;
  }

 private:
  void setLayouts(const Ref<VertexBuffer> &vertexBuffer);

 private:
  UInt32 m_id = 0;
  std::vector<Ref<VertexBuffer>> m_vertexBuffers;
  Ref<IndexBuffer> m_indexBuffer;
};
}  // namespace Neat