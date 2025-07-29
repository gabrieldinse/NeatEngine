#include "NeatPCH.hpp"

#include "Neat/Utils/LoadImage.hpp"

#include <stb_image.h>

namespace Neat {
std::expected<Image, ImageLoadError> loadImage(const std::string filepath,
                                               bool flipVertically) {
  NT_PROFILE_FUNCTION();
  Int32 width;
  Int32 height;
  Int32 channels;
  stbi_set_flip_vertically_on_load(static_cast<int>(flipVertically));
  UChar* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

  if (not data) {
    return std::unexpected{ImageLoadError{filepath}};
  }

  return Image{data, width, height, channels};
}

Image::Image(UChar* data, Int32 width, Int32 height, Int32 channels)
    : m_data(data), m_width(width), m_height(height), m_channels(channels) {}

Image::Image(Image&& other) noexcept
    : m_data(other.m_data),
      m_width(other.m_width),
      m_height(other.m_height),
      m_channels(other.m_channels) {
  other.m_data = nullptr;
}

Image& Image::operator=(Image&& other) noexcept {
  if (this != &other) {
    if (m_data) {
      stbi_image_free(m_data);
    }
    m_width = other.m_width;
    m_height = other.m_height;
    m_channels = other.m_channels;
    m_data = other.m_data;
    other.m_data = nullptr;
  }
  return *this;
}

Image::~Image() {
  if (m_data) {
    stbi_image_free(m_data);
  }
}
};  // namespace Neat