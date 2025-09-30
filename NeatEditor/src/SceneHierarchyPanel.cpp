#include <filesystem>

#include "Neat/Components/Components.hpp"
#include "Neat/Utils/TypeConversions.hpp"
#include "Neat/Graphics/Color.hpp"

#include "SceneHierarchyPanel.hpp"
#include "ContentBrowserPanel.hpp"

#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

namespace Neat {
SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene> &scene)
    : m_scene(scene) {
  m_componentWidgetsRegistry.registerComponent<TransformComponent>(
      "Transform", []([[maybe_unused]] const Ref<EntityManager> &entityManager,
                      Entity &entity) {
        auto transform = entity.getComponent<TransformComponent>();
        drawVector3FControl("Position", transform->position);
        drawVector3FControl("Rotation", transform->rotation);
        drawVector3FControl("Scale", transform->scaling, 1.0f);
      });

  m_componentWidgetsRegistry.registerComponent<CameraComponent>(
      "Camera", []([[maybe_unused]] const Ref<EntityManager> &entityManager,
                   Entity &entity) {
        auto camera = entity.getComponent<CameraComponent>();
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

  m_componentWidgetsRegistry.registerComponent<RenderableSpriteComponent>(
      "Sprite", []([[maybe_unused]] const Ref<EntityManager> &entityManager,
                   Entity &entity) {
        auto sprite = entity.getComponent<RenderableSpriteComponent>();
        ImGui::ColorEdit4("Color", sprite->color.data());

        ImGui::Button("Texture", ImVec2{100.0f, 0.0f});
        if (ImGui::BeginDragDropTarget()) {
          const ImGuiPayload *dragDropPayload =
              ImGui::AcceptDragDropPayload("Content Browser Item");
          if (dragDropPayload) {
            const char *relativePath =
                static_cast<const char *>(dragDropPayload->Data);
            std::filesystem::path textureFilepath{
                (std::filesystem::path(ContentBrowserPanel::getAssetsPath()) /
                 relativePath)};
            std::string textureFilepathStr{textureFilepath.string()};
            Ref<Texture2D> texture = Texture2D::create(textureFilepathStr);
            if (texture->isLoaded()) {
              sprite->texture = texture;
            } else {
              NT_CORE_ERROR("Could not load texture from path: {}",
                            textureFilepathStr);
            }
          }
          ImGui::EndDragDropTarget();
        }

        ImGui::DragFloat("Tiling Factor", &sprite->tilingFactor, 0.1f, 0.1f);
      });
}

void SceneHierarchyPanel::setScene(const Ref<Scene> &scene) {
  m_scene = scene;
  m_selectedEntity = Entity{};
}

void SceneHierarchyPanel::onUpdate() {
  ImGui::Begin("Scene Hierarchy");
  for (Entity entity : m_scene->getEntityManager()->entities()) {
    drawEntityNode(entity);
  }

  if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
    m_selectedEntity = Entity{};
  }

  // Right-click on blank space
  if (ImGui::BeginPopupContextWindow(0, 1 | ImGuiPopupFlags_NoOpenOverItems)) {
    if (ImGui::MenuItem("Create Empty Entity")) {
      Entity entity = m_scene->getEntityManager()->createEntity();
      entity.addComponent<LabelComponent>("Empty Entity");
    }
    ImGui::EndPopup();
  }

  ImGui::End();

  ImGui::Begin("Properties");
  if (m_selectedEntity) {
    drawComponentNodes(m_selectedEntity);
  }
  ImGui::End();
}

void SceneHierarchyPanel::drawEntityNode(Entity &entity) {
  if (not entity.hasComponent<LabelComponent>()) {
    return;
  }

  const auto &label = entity.getComponent<LabelComponent>();
  // TODO review these flags;
  ImGuiTreeNodeFlags flags =
      ((m_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
      ImGuiTreeNodeFlags_OpenOnArrow;
  flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

  if (ImGui::TreeNodeEx(reinterpret_cast<void *>(static_cast<UInt64>(entity)),
                        flags, "%s", label->getRawLabel())) {
    if (ImGui::IsItemClicked()) {
      m_selectedEntity = entity;
    }

    bool entityDestroyed = false;
    if (ImGui::BeginPopupContextItem("Entity Settings")) {
      if (ImGui::MenuItem("Destroy Entity")) {
        entityDestroyed = true;
      }
      ImGui::EndPopup();
    }

    ImGui::TreePop();

    if (entityDestroyed) {
      entity.destroy();
      if (m_selectedEntity.id() == entity.id()) {
        m_selectedEntity = {};
      }
    }
  }
}

void SceneHierarchyPanel::drawComponentNodes(Entity &entity) {
  if (entity.hasComponent<LabelComponent>()) {
    auto label = entity.getComponent<LabelComponent>();
    std::array<char, 256> buffer{};
    strncpy(buffer.data(), label->getRawLabel(), buffer.size());
    if (ImGui::InputText("##Label", buffer.data(), buffer.size())) {
      label->label = std::string{buffer.data()};
    }
  }

  ImGui::SameLine();
  ImGui::PushItemWidth(-1);
  drawAddComponentButton();
  ImGui::PopItemWidth();

  m_componentWidgetsRegistry.drawAllComponents(m_scene->getEntityManager(),
                                               entity);
}

void SceneHierarchyPanel::drawAddComponentButton() {
  if (ImGui::Button("Add Component")) {
    ImGui::OpenPopup("Add Component");
  }

  if (ImGui::BeginPopup("Add Component")) {
    if (ImGui::MenuItem("Transform")) {
      m_selectedEntity.addComponent<TransformComponent>();
      ImGui::CloseCurrentPopup();
    }

    if (ImGui::MenuItem("Camera")) {
      m_selectedEntity.addComponent<CameraComponent>(
          OrthographicProperties{1600, 900});
      ImGui::CloseCurrentPopup();
    }

    if (ImGui::MenuItem("Sprite")) {
      m_selectedEntity.addComponent<RenderableSpriteComponent>();
      ImGui::CloseCurrentPopup();
    }

    ImGui::EndPopup();
  }
}

void SceneHierarchyPanel::drawVector3FControl(const std::string label,
                                              Vector3F &values,
                                              float resetValue,
                                              float columnWidth) {
  ImGuiIO &io = ImGui::GetIO();
  auto boldFont = io.Fonts->Fonts[0];

  ImGui::PushID(label.c_str());

  ImGui::Columns(2);
  ImGui::SetColumnWidth(0, columnWidth);
  ImGui::Text("%s", label.c_str());
  ImGui::NextColumn();

  ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

  float lineHeight =
      GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
  ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

  ImVec4 xColor = toImVec4(Color::vermilion);
  ImVec4 xColorHovered =
      toImVec4(Color::vermilion + Vector4F{0.1f, 0.1f, 0.1f, 0.0f});
  ImGui::PushStyleColor(ImGuiCol_Button, xColor);
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, xColorHovered);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, xColor);
  ImGui::PushFont(boldFont);
  if (ImGui::Button("X", buttonSize)) values.x() = resetValue;
  ImGui::PopFont();
  ImGui::PopStyleColor(3);
  ImGui::SameLine();
  ImGui::DragFloat("##X", &values.x(), 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImVec4 yColor = toImVec4(Color::appleGreen);
  ImVec4 yColorHovered =
      toImVec4(Color::appleGreen + Vector4F{0.1f, 0.1f, 0.1f, 0.0f});
  ImGui::PushStyleColor(ImGuiCol_Button, yColor);
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, yColorHovered);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, yColor);
  ImGui::PushFont(boldFont);
  if (ImGui::Button("Y", buttonSize)) values.y() = resetValue;
  ImGui::PopFont();
  ImGui::PopStyleColor(3);
  ImGui::SameLine();
  ImGui::DragFloat("##Y", &values.y(), 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImVec4 zColor = toImVec4(Color::mediumDodgerBlue);
  ImVec4 zColorHovered =
      toImVec4(Color::mediumDodgerBlue + Vector4F{0.1f, 0.1f, 0.1f, 0.0f});
  ImGui::PushStyleColor(ImGuiCol_Button, zColor);
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, zColorHovered);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, zColor);
  ImGui::PushFont(boldFont);
  if (ImGui::Button("Z", buttonSize)) values.z() = resetValue;
  ImGui::PopFont();
  ImGui::PopStyleColor(3);
  ImGui::SameLine();
  ImGui::DragFloat("##Z", &values.z(), 0.1f, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();

  ImGui::PopStyleVar();

  ImGui::Columns(1);

  ImGui::PopID();
}

}  // namespace Neat