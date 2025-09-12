#pragma once

#include <string>
#include <functional>

#include "Neat/ECS/ECS.hpp"

namespace Neat {
using WidgetFunction = std::function<void(const Ref<EntityManager>&, Entity&)>;

struct ComponentWidgetProperties {
  std::string name;
  WidgetFunction draw;
  WidgetFunction add;
  WidgetFunction remove;
};

class ComponentWidgetsRegistry {
 public:
  ComponentWidgetsRegistry() = default;
  ComponentWidgetsRegistry(Ref<EntityManager> entityManager)
      : m_entityManager(entityManager) {}

  void drawAllComponents(Entity& entity);
  template <typename Component>
  void registerComponent(const std::string& name, WidgetFunction drawFunction);

 private:
  void drawComponent(Entity& entity, BaseComponent::Family family,
                     ComponentWidgetProperties widgetProperties);

 private:
  Ref<EntityManager> m_entityManager;
  std::map<BaseComponent::Family, ComponentWidgetProperties> m_registry;
};

template <typename Component>
void addComponentAction(
    [[maybe_unused]] const Ref<EntityManager>& entityManager, Entity& entity) {
  entity.addComponent<Component>();
}

template <typename Component>
void removeComponentAction(
    [[maybe_unused]] const Ref<EntityManager>& entityManager, Entity& entity) {
  entity.removeComponent<Component>();
}

template <typename Component>
void ComponentWidgetsRegistry::registerComponent(const std::string& name,
                                                 WidgetFunction drawFunction) {
  m_registry[m_entityManager->getComponentFamily<Component>()] = {
      name, drawFunction, addComponentAction<Component>,
      removeComponentAction<Component>};
}
}  // namespace Neat