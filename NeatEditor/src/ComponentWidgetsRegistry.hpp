#pragma once

#include <string>
#include <functional>
#include <vector>

#include "Neat/ECS/ECS.hpp"

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

namespace Neat {
using WidgetFunction = std::function<void(const Ref<EntityManager>&, Entity&)>;

struct ComponentWidgetProperties {
  using WidgetDrawFunction = std::function<void(
      const std::string&, const Ref<EntityManager>&, Entity&)>;
  std::string name;
  WidgetDrawFunction draw;
};

class ComponentWidgetsRegistry {
 public:
  ComponentWidgetsRegistry() = default;

  void drawAllComponents(const Ref<EntityManager>& entityManager,
                         Entity& entity);
  template <typename Component>
  void registerComponent(const std::string& name, WidgetFunction drawFunction);

 private:
  std::vector<ComponentWidgetProperties> m_registry;
};

template <typename Component>
void ComponentWidgetsRegistry::registerComponent(const std::string& name,
                                                 WidgetFunction drawFunction) {
  m_registry.push_back(ComponentWidgetProperties{
      name,
      [drawFunction](const std::string& name,
                     const Ref<EntityManager>& entityManager, Entity& entity) {
        if (entity.hasComponent<Component>()) {
          const ImGuiTreeNodeFlags treeNodeFlags =
              ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed |
              ImGuiTreeNodeFlags_SpanAvailWidth |
              ImGuiTreeNodeFlags_AllowItemOverlap |
              ImGuiTreeNodeFlags_FramePadding;

          ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
          ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 4});
          float lineHeight =
              GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
          ImGui::Separator();

          bool treeNodeOpened = ImGui::TreeNodeEx(
              reinterpret_cast<void*>(
                  entityManager->getComponentFamily<Component>()),
              treeNodeFlags, "%s", name.c_str());
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
            drawFunction(entityManager, entity);
            ImGui::TreePop();
          }

          if (removeComponent) {
            entity.removeComponent<Component>();
          }
        }
      }});
}
}  // namespace Neat