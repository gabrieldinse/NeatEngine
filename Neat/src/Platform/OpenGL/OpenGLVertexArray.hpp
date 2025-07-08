#pragma once

#include "Neat/Core/Types.hpp"
#include "Neat/Graphics/VertexBuffer.hpp"
#include "Neat/Graphics/IndexBuffer.hpp"
#include "Neat/Graphics/VertexArray.hpp"

namespace Neat {
class OpenGLVertexArray : public VertexArray {
 public:
  OpenGLVertexArray();
  virtual ~OpenGLVertexArray();
  virtual void bind() const override;
  virtual void unbind() const override;

  virtual void addVertexBuffer(
      const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
  virtual void setIndexBuffer(
      const std::shared_ptr<IndexBuffer> &indexBuffer) override;

  virtual const std::vector<std::shared_ptr<VertexBuffer>> &getVertexBuffers()
      const override {
    return m_vertexBuffers;
  }

  virtual const std::shared_ptr<IndexBuffer> &getIndexBuffer() const override {
    return m_indexBuffer;
  }

 private:
  UInt32 m_id = 0;
  std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
  std::shared_ptr<IndexBuffer> m_indexBuffer;
};
}  // namespace Neat