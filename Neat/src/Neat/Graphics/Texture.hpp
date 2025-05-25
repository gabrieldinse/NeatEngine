#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "Neat/Core/Types.hpp"
#include "Neat/Math/Vector.hpp"

namespace Neat {
class Texture {
public:
  virtual ~Texture() = default;

  virtual Int32 getWidth() const = 0;
  virtual Int32 getHeight() const = 0;

  virtual void setData(void *data, UInt32 size) = 0;

  virtual void bind(UInt32 slot) const = 0;
};

class Texture2D : public Texture {
public:
  Texture2D(Int32 width, Int32 height);
  Texture2D(const std::string &filepath);
  ~Texture2D();

  Int32 getWidth() const { return m_width; }
  Int32 getHeight() const { return m_height; }

  virtual const Vector2F *getCoordinates() const { return m_coordinates; };

  void setData(void *data, UInt32 size);

  void bind(UInt32 unit) const;

  bool operator==(const Texture2D &other) const { return (m_id == other.m_id); }

private:
  UInt32 m_id;
  Int32 m_width;
  Int32 m_height;
  UInt32 m_internalFormat;
  UInt32 m_dataFormat;
  const Vector2F m_coordinates[4] = {
      {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
};
} // namespace Neat