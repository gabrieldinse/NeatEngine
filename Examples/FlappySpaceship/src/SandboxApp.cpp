#include <memory>

#include "ExampleLayer.hpp"
#include <Neat.hpp>
#include <Neat/Core/Main.hpp>

class Sandbox : public Neat::Application {
public:
  Sandbox() { pushLayer<ExampleLayer>(getEventDispatcher()); }

  ~Sandbox() {}
};

Neat::Scope<Neat::Application> Neat::createApplication() {
  return Neat::makeScope<Sandbox>();
}