#pragma once

#include <memory>
#include <utility>
#include <unordered_map>

#include "Neat/Core/Log.h"
#include "Neat/Core/Exceptions.h"
#include "Neat/ECS/System.h"
#include "Neat/Helper/NonCopyable.h"


namespace Neat
{
   class SystemManager : public NonCopyable
   {
   public:
      SystemManager(EntityManager& entityManager, EventManager& eventManager)
         : m_entityManager(entityManager), m_eventManager(eventManager) {}


      void init()
      {
         for(auto& [_, system] : m_systems)
            system->init(m_eventManager);

         m_initialized = true;
      }

      template <typename S>
      void addSystem(std::shared_ptr<S> system)
      {
         m_systems[S::getFamily()] = system;
      }

      template <typename S, typename... Args>
      std::shared_ptr<S> addSystem(Args&&... args)
      {
         auto system = std::make_shared<S>(std::forward<Args>(args)...);
         addSystem(system);

         return system;
      }

      template <typename S>
      std::shared_ptr<S> getSystem()
      {
         auto it = m_systems.find(S::getFamily());

         if (it == m_systems.end())
            throw InvalidSystemError();

         return
            std::shared_ptr<S>(std::static_pointer_cast<S>(it->second));
      }

      void updateAll(DeltaTime deltaTime)
      {
         if (!m_initialized)
            throw SystemManagerNotInitializedError();

         for (auto& [_, system] : m_systems)
            system->update(m_entityManager, m_eventManager, deltaTime);
      }

      void renderAll()
      {
         if (!m_initialized)
            throw SystemManagerNotInitializedError();

         for (auto& [_, system] : m_systems)
            system->render(m_entityManager, m_eventManager);
      }

   private:
      bool m_initialized = false;
      EntityManager& m_entityManager;
      EventManager& m_eventManager;
      std::unordered_map<BaseSystem::Family, std::shared_ptr<BaseSystem>> m_systems;
   };
}