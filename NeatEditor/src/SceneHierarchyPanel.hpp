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
  void drawComponentNodes(Entity &entity);
  void drawAddComponentButton();
  template <typename Component, typename Function>
  void drawComponent(const std::string &name, Entity &entity,
                     Function function);
  static void drawVector3FControl(const std::string label, Vector3F &values,
                                  float resetValue = 0.0f,
                                  float columnWidth = 100.0f);

 private:
  Ref<Scene> m_scene;
  Entity m_selectedEntity;
};
}  // namespace Neat