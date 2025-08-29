#pragma once

#include "Neat/Scene/Scene.hpp"

namespace Neat {
class SceneHierarchyPanel {
 public:
  SceneHierarchyPanel() = default;
  SceneHierarchyPanel(const Ref<Scene> &scene);
  ~SceneHierarchyPanel() = default;

  void setScene(const Ref<Scene> &scene);
  void onUpdate();

 private:
  void drawEntityNode(Entity &entity);
  void drawEntityComponents(Entity &entity);

 private:
  Ref<Scene> m_scene;
  Entity m_selectedEntity;
};
}  // namespace Neat