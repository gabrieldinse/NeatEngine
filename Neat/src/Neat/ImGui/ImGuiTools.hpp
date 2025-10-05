#pragma once

#include "Neat/Utils/FPSCounter.hpp"
#include "Neat/Graphics/Renderer2D.hpp"

namespace Neat {
struct ImGuiTools {
  static FPSCounter fpsCounter;

  static void onStatsUpdate(const Entity &hoveredEntity);
};
}  // namespace Neat