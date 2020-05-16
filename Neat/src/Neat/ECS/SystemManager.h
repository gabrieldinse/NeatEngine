#pragma once

#include <memory>
#include <utility>
#include <unordered_map>

#include "Neat/Core/Log.h"
#include "Neat/Core/Exceptions.h"
#include "Neat/ECS/System.h"


namespace Neat
{
   class SystemManager
   {
      SystemManager(EntityManager& entityManager, EventManager& eventManager)
         : m_entityManager(entityManager), m_eventManager(eventManager) {}

      SystemManager(const SystemManager&) = delete;
      SystemManager& operator = (const SystemManager &) = delete;

      void init()
      {
         for(auto& pair : m_systems)
            pair.second->init(m_eventManager);

         m_initialized = true;
      }

      template <typename S>
      void add(std::shared_ptr<S> system)
      {
         m_systems.insert(std::make_pair(S::getFamily(), system));
      }

      template <typename S, typename... Args>
      std::shared_ptr<S> add(Args&&... args)
      {
         auto system = std::make_shared<S>(std::forward<Args>(args)...);
         add(system);
      }

      template <typename S>
      std::shared_ptr<S> system()
      {
         auto it = m_systems.find(S::getFamily());

         if (it == m_systems.end())
            throw InvalidSystemError();

         return
            std::shared_ptr<S>(std::static_pointer_cast<S>(it->second));
      }

      void updateAll(Timestep deltaTime)
      {
         if (!m_initialized)
            throw SystemManagerNotInitializedError();

         for (auto& pair : m_systems)
            pair.second->update(m_entityManager, m_eventManager, deltaTime);
      }

      void renderAll(Timestep deltaTime)
      {
         if (!m_initialized)
            throw SystemManagerNotInitializedError();

         for (auto& pair : m_systems)
            pair.second->render(m_entityManager, m_eventManager);
      }

   private:
      bool m_initialized = false;
      EntityManager& m_entityManager;
      EventManager& m_eventManager;
      std::unordered_map<BaseSystem::Family, std::shared_ptr<BaseSystem>> m_systems;
   };
}