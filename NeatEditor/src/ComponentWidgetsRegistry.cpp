#include "ComponentWidgetsRegistry.hpp"

namespace Neat {
void ComponentWidgetsRegistry::drawAllComponents(
    const Ref<EntityManager> &entityManager, Entity &entity) {
  for (const auto &widgetProperties : m_registry) {
    widgetProperties.draw(widgetProperties.name, entityManager, entity);
  }
}
}  // namespace Neat