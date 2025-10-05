#pragma once

#include "Utils/FPSCounter.hpp"
#include "Graphics/Renderer2D.hpp"

namespace Neat {
struct ImGuiTools {
  static FPSCounter fpsCounter;

  static void onStatsUpdate(const Entity &hoveredEntity);
};
}  // namespace Neat