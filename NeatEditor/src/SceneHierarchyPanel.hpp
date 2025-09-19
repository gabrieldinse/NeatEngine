#pragma once

#include "ComponentWidgetsRegistry.hpp"

#include "Neat/Scene/Scene.hpp"

namespace Neat {
class SceneHierarchyPanel {
 public:
  SceneHierarchyPanel() = default;
  SceneHierarchyPanel(const Ref<Scene> &scene);
  ~SceneHierarchyPanel() = default;

  void setScene(const Ref<Scene> &scene);
  void onUpdate();
  Entity &getSelectedEntity() { return m_selectedEntity; }

 private:
  void drawEntityNode(Entity &entity);
  void drawComponentNodes(Entity &entity);
  void drawAddComponentButton();
  static void drawVector3FControl(const std::string label, Vector3F &values,
                                  float resetValue = 0.0f,
                                  float columnWidth = 100.0f);

 private:
  Ref<Scene> m_scene;
  Entity m_selectedEntity;
  ComponentWidgetsRegistry m_componentWidgetsRegistry;
};
}  // namespace Neat