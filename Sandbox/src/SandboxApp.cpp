#include <memory>

#include <Neat.hpp>
#include <Neat/Main.hpp>
#include "ExampleLayer.hpp"

class Sandbox : public Neat::Application {
 public:
  Sandbox()
      : Neat::Application{Neat::ApplicationProperties{
            Neat::WindowProperties{"Sandbox App"}}} {
    pushLayer<ExampleLayer>(getEventDispatcher());
  }

  ~Sandbox() {}
};

Neat::Scope<Neat::Application> Neat::createApplication(
    [[maybe_unused]] const ApplicationCommandLineArguments &commandLineArgs) {
  return Neat::makeScope<Sandbox>();
}
