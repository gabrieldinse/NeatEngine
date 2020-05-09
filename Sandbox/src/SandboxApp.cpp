#include <memory>

#include <Neat.h>
#include <Neat/Core/EntryPoint.h>

#include <ImGui/imgui.h>

#include "Sandbox2D.h"


class Sandbox : public Neat::Application
{
public:
   Sandbox()
   {
      this->pushLayer<Sandbox2D>();
   } 

   ~Sandbox()
   {
   }
};


std::unique_ptr<Neat::Application> Neat::createApplication()
{
	return std::make_unique<Sandbox>();
}