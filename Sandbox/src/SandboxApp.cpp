#include <memory>

#include <Neat.hpp>
#include <Neat/Core/Main.hpp>
#include "Neat/Helper/FPSCounter.hpp"
#include "ExampleLayer.hpp"

// #include "Sandbox2D.hpp"

class Sandbox : public Neat::Application {
 public:
  Sandbox() { pushLayer<ExampleLayer>(); }

  ~Sandbox() {}
};

std::unique_ptr<Neat::Application> Neat::createApplication() {
  return std::make_unique<Sandbox>();
}