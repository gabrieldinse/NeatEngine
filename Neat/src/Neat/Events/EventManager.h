#pragma once

#include <vector>

#include "Neat/Core/Exceptions.h"
#include "Neat/Core/Log.h"
#include "Neat/Events/EventListener.h"


namespace Neat
{
   class EventManager
   {
   public:
      EventManager() = default;
      virtual ~EventManager() = default;

      EventManager(const EventManager&) = delete;
      EventManager& operator=(const EventManager &) = delete;


      template <typename E, typename Listener>
      void addListener(Listener& listener,
         EventPriority priority = EventPriority::Lowest,
         bool ignoreIfHandled = false)
      {
         auto event_connection = getEventConnection(Event<E>::getFamily());
         auto connection_id = event_connection->addListener<E>(
            listener, priority, ignoreIfHandled);

         BaseEventListener& base = listener;
         base.m_listenersMap.insert(
            std::make_pair(
               Event<E>::getFamily(),
               std::make_pair(
                  std::weak_ptr<EventConnection>(event_connection),
                  connection_id
               )
            )
         );
         NT_CORE_TRACE((std::size_t) & base.m_listenersMap);
      }

      template <typename E, typename Listener>
      void removeListener(Listener& listener)
      {
         BaseEventListener& base = listener;

         if (base.m_listenersMap.find(Event<E>::getFamily())
            == base.m_listenersMap.end())
            throw EventSubscriptionError();

         auto& [event_connection, connection_id] =
            base.m_listenersMap[Event<E>::getFamily()];

         if (!event_connection.expired())
            event_connection.lock()->removeListener(connection_id);

         base.m_listenersMap.erase(Event<E>::getFamily());
      }


      template <typename E>
      void publish(const E& event)
      {
         auto event_connection = getEventConnection(Event<E>::getFamily());
         event_connection->publishEvent<E>(event);
      }

      template <typename E>
      void publish(std::unique_ptr<E> event)
      {
         auto event_connection = getEventConnection(Event<E>::getFamily());
         event_connection->publishEvent<E>(event);
      }

      template <typename E, typename... Args>
      void publish(Args&&... args)
      {
         auto event_connection = getEventConnection(Event<E>::getFamily());
         event_connection->publishEvent<E>(std::forward<Args>(args)...);
      }


      UInt getNumberOfListeners() const
      {
         UInt count = 0;
         for (auto& event_connection : m_eventConnections)
            if (event_connection)
               count += (UInt)event_connection->size();

         return count;
      }

   private:
      std::shared_ptr<EventConnection>& getEventConnection(
         BaseEvent::Family family)
      {
         if (family >= m_eventConnections.size())
            m_eventConnections.resize((std::size_t)family + 1);

         if (!m_eventConnections[family])
            m_eventConnections[family] = std::make_shared<EventConnection>();

         return m_eventConnections[family];
      }

   private:
      std::vector<std::shared_ptr<EventConnection>> m_eventConnections;
   };


}