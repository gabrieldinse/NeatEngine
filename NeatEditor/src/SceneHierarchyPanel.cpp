#include "NeatPCH.hpp"

#include "Neat/Components/Components.hpp"

#include "SceneHierarchyPanel.hpp"

#include <ImGui/imgui.h>

namespace Neat {
SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene> &scene)
    : m_scene(scene) {}

void SceneHierarchyPanel::setScene(const Ref<Scene> &scene) { m_scene = scene; }

void SceneHierarchyPanel::onUpdate() {
  ImGui::Begin("Scene Hierarchy");
  for (Entity entity : m_scene->getEntityManager()->entities()) {
    drawEntityNode(entity);
  }

  if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
    m_selectedEntity = Entity{};
  }
  ImGui::End();

  ImGui::Begin("Properties");
  if (m_selectedEntity) {
    drawEntityComponents(m_selectedEntity);
  }
  ImGui::End();
}

void SceneHierarchyPanel::drawEntityNode(Entity &entity) {
  if (not entity.hasComponent<LabelComponent>()) {
    return;
  }

  const auto &label = entity.getComponent<LabelComponent>();
  ImGuiTreeNodeFlags flags =
      ((m_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
      ImGuiTreeNodeFlags_OpenOnArrow;

  bool node_opened =
      ImGui::TreeNodeEx(reinterpret_cast<void *>(static_cast<UInt64>(entity)),
                        flags, "%s", label->getRawLabel());
  if (ImGui::IsItemClicked()) {
    m_selectedEntity = entity;
  }

  if (node_opened) {
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
    // TODO removed hardcoded ID
    bool node_opened = ImGui::TreeNodeEx(reinterpret_cast<void *>(9283742),
                                         flags, "%s", label->getRawLabel());

    if (node_opened) {
      ImGui::TreePop();
    }

    ImGui::TreePop();
  }
}

void SceneHierarchyPanel::drawEntityComponents(Entity &entity) {
  if (entity.hasComponent<LabelComponent>()) {
    auto label = entity.getComponent<LabelComponent>();
    // TODO use a string instead of a buffer + copy to label string?
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, label->getRawLabel(), sizeof(buffer));
    if (ImGui::InputText("Label", buffer, sizeof(buffer))) {
      label->label = std::string(buffer);
    }
  }

  if (entity.hasComponent<TransformComponent>()) {
    // TODO use a proper ID
    if (ImGui::TreeNodeEx(
            reinterpret_cast<void *>(typeid(TransformComponent).hash_code()),
            ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
      auto transform = entity.getComponent<TransformComponent>();
      ImGui::DragFloat3("Position", transform->position.dataPointer(), 0.1f);
      ImGui::DragFloat3("Rotation", transform->rotation.dataPointer(), 0.1f);
      ImGui::DragFloat3("Scale", transform->scaling.dataPointer(), 0.1f);
      ImGui::TreePop();
    }
  }
}

}  // namespace Neat