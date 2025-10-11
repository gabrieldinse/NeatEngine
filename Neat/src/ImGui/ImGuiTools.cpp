#include "NeatPCH.hpp"

#include "ImGuiTools.hpp"

#include "Components/LabelComponent.hpp"

#include <imgui.h>

namespace Neat {
FPSCounter ImGuiTools::fpsCounter;

void ImGuiTools::onStatsUpdate(const Entity &hoveredEntity) {
  ImGuiTools::fpsCounter.start();
  ImGuiTools::fpsCounter.addFrame();
  auto stats = Renderer2D::getStats();
  ImGui::Begin("Stats");

  std::string entityLabel{"None"};
  std::string entityIndex{"N/A"};
  if (hoveredEntity) {
    auto labelCompOpt = hoveredEntity.getComponent<LabelComponent>();
    if (labelCompOpt) {
      const auto &labelComponent = *labelCompOpt;
      entityLabel = labelComponent->label;
      entityIndex = std::to_string(hoveredEntity.id().index());
    }
  }
  ImGui::Text("Hovered Entity: %s", entityLabel.c_str());
  ImGui::Text("Hovered Entity Index: %s", entityIndex.c_str());

  ImGui::Text("FPS: %.2f", ImGuiTools::fpsCounter.getFPS());

  ImGui::Text("Number of draw calls: %d", stats.drawCalls);
  ImGui::Text("Number of quads: %d", stats.quadCount);
  ImGui::Text("Number of indexes: %d", stats.getTotalIndexCount());
  ImGui::Text("Number of vertexes: %d\n", stats.getTotalVertexCount());
  ImGui::End();  // Stats
}
}  // namespace Neat