#include <memory>

#include "GameLayer.hpp"
#include <Neat.hpp>
#include <Neat/Core/Main.hpp>

class FlappySpaceshipApp : public Neat::Application {
 public:
  FlappySpaceshipApp() { pushLayer<GameLayer>(getEventDispatcher()); }

  ~FlappySpaceshipApp() {}
};

Neat::Scope<Neat::Application> Neat::createApplication() {
  return Neat::makeScope<FlappySpaceshipApp>();
}