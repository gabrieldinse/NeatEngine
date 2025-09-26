#include <memory>

#include "GameLayer.hpp"
#include <Neat.hpp>
#include <Neat/Core/Main.hpp>

class FlappySpaceshipApp : public Neat::Application {
 public:
  FlappySpaceshipApp()
      : Neat::Application{Neat::ApplicationProperties{
            Neat::WindowProperties{"Neat Editor"}}} {
    pushLayer<GameLayer>(getEventDispatcher());
  }

  ~FlappySpaceshipApp() {}
};

Neat::Scope<Neat::Application> Neat::createApplication(
    [[maybe_unused]] const ApplicationCommandLineArguments &commandLineArgs) {
  return Neat::makeScope<FlappySpaceshipApp>();
}