#include <memory>

#include <Neat.hpp>
#include <Neat/Core/Main.hpp>
#include "EditorLayer.hpp"

namespace Neat {
class Editor : public Application {
 public:
  Editor() {
    init(ApplicationProperties{WindowProperties{"Neat Editor"}});
    pushLayer<EditorLayer>(getEventDispatcher());
  }

  ~Editor() {}
};

Scope<Application> createApplication() { return makeScope<Editor>(); }
}  // namespace Neat