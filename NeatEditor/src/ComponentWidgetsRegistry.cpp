#include "ComponentWidgetsRegistry.hpp"

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

namespace Neat {
void ComponentWidgetsRegistry::drawAllComponents(Entity &entity) {
  for (const auto &[family, widgetProperties] : m_registry) {
    drawComponent(entity, family, widgetProperties);
  }
}

void ComponentWidgetsRegistry::drawComponent(Entity &entity,
                                             BaseComponent::Family family,
                                             ComponentWidgetProperties widget) {
  if (entity.hasComponent(family)) {
    const ImGuiTreeNodeFlags treeNodeFlags =
        ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
        ImGuiTreeNodeFlags_SpanAvailWidth |
        ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

    ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 4});
    float lineHeight =
        GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImGui::Separator();

    bool treeNodeOpened =
        ImGui::TreeNodeEx(reinterpret_cast<void *>(family), treeNodeFlags, "%s",
                          widget.name.c_str());
    ImGui::PopStyleVar();
    ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);

    ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
    if (ImGui::Button("+", ImVec2{lineHeight, lineHeight})) {
      ImGui::OpenPopup("Component Settings");
    }

    bool removeComponent = false;
    if (ImGui::BeginPopup("Component Settings")) {
      if (ImGui::MenuItem("Remove Component")) {
        removeComponent = true;
      }
      ImGui::EndPopup();
    }

    if (treeNodeOpened) {
      widget.draw(m_entityManager, entity);
      ImGui::TreePop();
    }

    if (removeComponent) {
      widget.remove(m_entityManager, entity);
    }
  }
}

}  // namespace Neat