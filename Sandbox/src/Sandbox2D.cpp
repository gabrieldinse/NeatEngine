#include <chrono>
#include <thread>

#include "Sandbox2D.hpp"

// struct Component1 {};
// struct Component2 {};
// struct Component3 {};
//
// class System1 : public Neat::System<System1>
//{
//    virtual void onUpdate(Neat::EntityManager& entityManager,
//       Neat::EventDispatcher& eventManager, double deltaTimeSeconds)
//       override
//    {
//       NT_TRACE("System 1 onUpdate");
//
//       for (auto& entity :
//          entityManager.entitiesWithComponents<Component2>())
//       {
//          NT_TRACE(entity);
//       }
//       NT_TRACE("");
//    }
// };
//
// class System2 : public Neat::System<System2>
//{
//    virtual void onUpdate(Neat::EntityManager& entityManager,
//       Neat::EventDispatcher& eventManager, double deltaTimeSeconds)
//       override
//    {
//       NT_TRACE("System 2 onUpdate");
//
//       for (auto& entity :
//          entityManager.entitiesWithComponents<Component1>())
//       {
//          NT_TRACE(entity);
//       }
//       NT_TRACE("");
//    }
// };
//
//
// Sandbox2D::Sandbox2D()
//{
//    //using namespace Neat;
//    //auto& event_manager = Neat::Application::get().events();
//    //EntityManager entity_manager(event_manager);
//    //SystemManager system_manager(entity_manager, event_manager);
//
//    //system_manager.addSystem<System1>();
//    //system_manager.addSystem<System2>();
//    //system_manager.init();
//
//    //auto entity1 = entity_manager.createEntity();
//    //entity1.addComponent<Component1>();
//    //entity1.addComponent<Component2>();
//
//    //auto entity2 = entity_manager.createEntity();
//    //entity2.addComponent<Component1>();
//    //entity2.addComponent<Component3>();
//
//    //auto entity3 = entity_manager.createEntity();
//    //entity3.addComponent<Component2>();
//    //entity3.addComponent<Component3>();
//
//    //Stopwatch timer;
//    //timer.start();
//    //while (true)
//    //{
//    //   system_manager.updateAll(timer.restart());
//
//    //   // Sleep for 1 second
//    //   std::chrono::duration<int, std::milli> timespan(3000);
//    //   std::this_thread::sleep_for(timespan);
//    //}
//
//    //NT_ASSERT(false, "");
// }
//
// void Sandbox2D::attach()
//{
//    this->checkerboardTexture = Neat::makeRef<Neat::Texture2D>(
//       "assets/textures/texture1.png");
//    this->spritesheetTexture = Neat::makeRef<Neat::Texture2D>(
//       "assets/textures/spritesheet1.png");
//    this->stairsTexture = Neat::SubTexture2D::createFromIndex(
//       *this->spritesheetTexture, { 7, 6 }, { 64, 64 });
//    this->stairsTexture2 = Neat::SubTexture2D::createFromIndex(
//       *this->spritesheetTexture, { 8, 6 }, { 64, 64 });
// }
//
// void Sandbox2D::detach()
//{
// }
//
// void Sandbox2D::onUpdate(double deltaTimeSeconds)
//{
// }
//
// void Sandbox2D::onRender()
//{
//    Neat::Renderer2D::resetStats();
//
//
//    Neat::RenderCommand::clearWithColor({0.35f, 0.35f, 0.55f, 1.0f});
//    Neat::Renderer2D::beginScene(this->cameraController.getCamera());
//
//    Neat::Renderer2D::drawQuad(
//       {1.0f, 0.0f}, {0.5f, 0.5f}, {0.7f, 0.5f, 0.3f, 1.0f});
//    Neat::Renderer2D::drawQuad(
//       {-1.2f, 0.0f}, {0.5f, 0.5f}, {0.35f, 0.3f, 0.9f, 1.0f});
//    Neat::Renderer2D::drawRotatedQuad(
//       { 0.0f, 0.75f, 1.5f}, { 0.5f, 0.5f }, 45.0f, { 0.65f, 0.78f, 0.2f, 1.0f
//       });
//    Neat::Renderer2D::drawQuad(
//       {0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, this->checkerboardTexture,
//       this->tint, 5.0f);
//
//    for (std::size_t i = 0; i < this->numberOfLines; ++i)
//       for (std::size_t j = 0; j < this->numberOfColumns; ++j)
//          Neat::Renderer2D::drawQuad(
//             { 0.1f * j, 0.1f * i},
//             { 0.1f, 0.1f },
//             { float(i) / this->numberOfLines, float(j) /
//             this->numberOfColumns, 1.0f, 1.0f });
//
//    Neat::Renderer2D::drawQuad(
//       { 0.0f, -0.5f, 0.5f }, { 1.0f, 1.0f }, this->stairsTexture);
//    Neat::Renderer2D::drawQuad(
//       { 1.0f, -0.5f, 0.5f }, { 1.0f, 1.0f }, this->stairsTexture2);
//
//    Neat::Renderer2D::endScene();
// }