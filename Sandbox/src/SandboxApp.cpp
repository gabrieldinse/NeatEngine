#include <memory>

#include <Neat.hpp>
#include <Neat/Core/Main.hpp>
#include "ExampleLayer.hpp"

class Sandbox : public Neat::Application {
 public:
  Sandbox()
      : Neat::Application{Neat::ApplicationProperties{
            Neat::WindowProperties{"Sandbox App"}}} {
    pushLayer<ExampleLayer>(getEventDispatcher());
  }

  ~Sandbox() {}

  // Temporary
  virtual void run() override {}
};

Neat::Scope<Neat::Application> Neat::createApplication() {
  return Neat::makeScope<Sandbox>();
}