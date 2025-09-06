#include "NeatPCH.hpp"

#include "Neat/Graphics/Color.hpp"

namespace Neat {
namespace Color {
Vector4F HSVToRGB(const Vector3F& hsv) {
  int h = static_cast<int>(hsv.x() * 360.0f);
  double s = hsv.y();
  double v = hsv.z();

  double c = s * v;
  double x = c * (1 - abs(fmod(h / 60.0, 2) - 1));
  double m = v - c;
  double rs, gs, bs;

  if (h >= 0 && h < 60) {
    rs = c;
    gs = x;
    bs = 0;
  } else if (h >= 60 && h < 120) {
    rs = x;
    gs = c;
    bs = 0;
  } else if (h >= 120 && h < 180) {
    rs = 0;
    gs = c;
    bs = x;
  } else if (h >= 180 && h < 240) {
    rs = 0;
    gs = x;
    bs = c;
  } else if (h >= 240 && h < 300) {
    rs = x;
    gs = 0;
    bs = c;
  } else {
    rs = c;
    gs = 0;
    bs = x;
  }

  return {rs + m, gs + m, bs + m, 1.0f};
}

Vector4F hexToRGBA(Int32 hex) {
  return {static_cast<float>(hex >> 24) / 255.0f,
          static_cast<float>(hex >> 16) / 255.0f,
          static_cast<float>(hex >> 8) / 255.0f,
          static_cast<float>(hex >> 0) / 255.0f};
}

Vector3F hexToRGB(Int32 hex) {
  return {static_cast<float>(hex >> 16) / 255.0f,
          static_cast<float>(hex >> 8) / 255.0f,
          static_cast<float>(hex >> 0) / 255.0f};
}
}  // namespace Color
}  // namespace Neat