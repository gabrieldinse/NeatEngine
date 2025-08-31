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

  if (ImGui::TreeNodeEx(reinterpret_cast<void *>(static_cast<UInt64>(entity)),
                        flags, "%s", label->getRawLabel())) {
    if (ImGui::IsItemClicked()) {
      m_selectedEntity = entity;
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

  drawComponent<TransformComponent>("Transform", entity, [](auto &transform) {
    ImGui::DragFloat3("Position", transform->position.raw(), 0.1f);
    ImGui::DragFloat3("Rotation", transform->rotation.raw(), 0.1f);
    ImGui::DragFloat3("Scale", transform->scaling.raw(), 0.1f);
  });

  drawComponent<CameraComponent>("Camera", entity, [&entity](auto &camera) {
    bool activeCamera = entity.hasComponent<ActiveCameraTagComponent>();
    bool activeCameraSelection = activeCamera;
    ImGui::Checkbox("Primary", &activeCameraSelection);
    if (activeCamera and not activeCameraSelection) {
      entity.removeComponent<ActiveCameraTagComponent>();
    } else if (not activeCamera and activeCameraSelection) {
      entity.addComponent<ActiveCameraTagComponent>();
    }

    const char *projectionTypes[] = {"Orthographic", "Perspective"};
    const char *currentProjectionType =
        projectionTypes[enumToInt(camera->getType())];

    if (ImGui::BeginCombo("Projection", currentProjectionType)) {
      for (UInt32 i = 0; i < 2; ++i) {
        const char *projectionType = projectionTypes[i];

        bool isSelected = currentProjectionType == projectionType;
        if (ImGui::Selectable(projectionType, isSelected)) {
          camera->setType(static_cast<CameraType>(i));
        }

        if (isSelected) {
          ImGui::SetItemDefaultFocus();
        }
      }
      ImGui::EndCombo();
    }

    switch (camera->getType()) {
      case CameraType::Orthographic: {
        float size = camera->getOrthographicSize();
        if (ImGui::DragFloat("Size", &size, 0.1f)) {
          camera->setOrthographicSize(size);
        }

        float near = camera->getOrthographicNear();
        if (ImGui::DragFloat("Near Clip", &near, 0.1f)) {
          camera->setOrthographicNear(near);
        }

        float far = camera->getOrthographicFar();
        if (ImGui::DragFloat("Far Clip", &far, 0.1f)) {
          camera->setOrthographicFar(far);
        }
      } break;
      case CameraType::Perspective: {
        float fov = camera->getPerspectiveFOV();
        if (ImGui::DragFloat("FOV", &fov, 1.0f, 1.0f, 179.0f)) {
          camera->setPerspectiveFOV(fov);
        }

        float near = camera->getPerspectiveNear();
        if (ImGui::DragFloat("Near Clip", &near)) {
          camera->setPerspectiveNear(near);
        }

        float far = camera->getPerspectiveFar();
        if (ImGui::DragFloat("Far Clip", &far)) {
          camera->setPerspectiveFar(far);
        }
      }
    }
  });
}

template <typename Component, typename Function>
void SceneHierarchyPanel::drawComponent(const std::string &name, Entity &entity,
                                        Function function) {
  if (entity.hasComponent<Component>()) {
    if (ImGui::TreeNodeEx(
            reinterpret_cast<void *>(typeid(Component).hash_code()),
            ImGuiTreeNodeFlags_DefaultOpen, "%s", name.c_str())) {
      auto component = entity.getComponent<Component>();
      function(component);
      ImGui::TreePop();
    }
  }
}

}  // namespace Neat