#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "Neat/Core/Types.hpp"
#include "Neat/Math/Vector.hpp"
#include "Neat/Graphics/Texture2D.hpp"

namespace Neat {
class OpenGLTexture2D : public Texture2D {
 public:
  OpenGLTexture2D(Int32 width, Int32 height);
  OpenGLTexture2D(const std::string &filepath);
  virtual ~OpenGLTexture2D();

  virtual Int32 getWidth() const override { return m_width; }
  virtual Int32 getHeight() const override { return m_height; }
  virtual UInt32 getRendererID() const override { return m_id; }

  virtual const Vector2F *getCoordinates() const override {
    return m_coordinates;
  };

  virtual void setData(void *data, UInt32 size) override;

  virtual void bind(UInt32 unit) const override;

  virtual bool operator==(const Texture &other) const override {
    return (m_id == other.getRendererID());
  }

  virtual void setMinification(Texture2DFilter minificationFilter) override;
  virtual void setMagnification(Texture2DFilter magnificationFilter) override;
  virtual void setWrapS(Texture2DWrapping wrapS) override;
  virtual void setWrapT(Texture2DWrapping wrapT) override;

 private:
  UInt32 m_id = 0;
  Int32 m_width;
  Int32 m_height;
  UInt32 m_internalFormat;
  UInt32 m_dataFormat;
  const Vector2F m_coordinates[4] = {
      {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
};

}  // namespace Neat