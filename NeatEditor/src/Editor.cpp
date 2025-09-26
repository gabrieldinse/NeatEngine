#include <memory>

#include <Neat.hpp>
#include <Neat/Core/Main.hpp>
#include "EditorLayer.hpp"

namespace Neat {
class Editor : public Application {
 public:
  Editor()
      : Application{ApplicationProperties{WindowProperties{"Neat Editor"}}} {
    pushLayer<EditorLayer>(getEventDispatcher());
  }

  ~Editor() {}
};

Scope<Application> createApplication(
    [[maybe_unused]] const ApplicationCommandLineArguments &commandLineArgs) {
  return makeScope<Editor>();
}
}  // namespace Neat