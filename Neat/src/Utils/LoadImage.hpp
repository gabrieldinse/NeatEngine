#pragma once

#include <expected>

#include "Core/Types.hpp"

namespace Neat {
struct ImageLoadError {
  std::string filepath;
};

class Image {
 public:
  ~Image();
  Image(UChar* data, Int32 width, Int32 height, Int32 channels);
  Image(const Image&) = delete;
  Image& operator=(const Image&) = delete;
  Image(Image&&) noexcept;
  Image& operator=(Image&&) noexcept;
  Int32 getWidth() const { return m_width; }
  Int32 getHeight() const { return m_height; }
  Int32 getChannels() const { return m_channels; }
  const UChar* data() const { return m_data; }

 private:
  UChar* m_data = nullptr;
  Int32 m_width = 0;
  Int32 m_height = 0;
  Int32 m_channels = 0;
};

std::expected<Image, ImageLoadError> loadImage(const std::string filepath,
                                               bool flipVertically = true);
}  // namespace Neat