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
      using EventsConnectionsVector =
         std::vector<std::shared_ptr<EventToListenersConnection>>;

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
         base.m_connectedEvents.insert(
            std::make_pair(
               Event<E>::getFamily(),
               std::make_pair(
                  std::weak_ptr<EventToListenersConnection>(event_connection),
                  connection_id
               )
            )
         );
         NT_CORE_TRACE((std::size_t) & base.m_connectedEvents);
      }

      template <typename E, typename Listener>
      void removeListener(Listener& listener)
      {
         BaseEventListener& base = listener;

         if (base.m_connectedEvents.find(Event<E>::getFamily())
            == base.m_connectedEvents.end())
            throw EventListenerError();

         auto& [event_connection, connection_id] =
            base.m_connectedEvents[Event<E>::getFamily()];

         if (!event_connection.expired())
            event_connection.lock()->removeListener(connection_id);

         base.m_connectedEvents.erase(Event<E>::getFamily());
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
         for (auto& event_connection : m_eventsConnections)
            if (event_connection)
               count += (UInt)event_connection->size();

         return count;
      }

   private:
      std::shared_ptr<EventToListenersConnection>& getEventConnection(
         BaseEvent::Family family)
      {
         if (family >= m_eventsConnections.size())
            m_eventsConnections.resize((std::size_t)family + 1);

         if (!m_eventsConnections[family])
            m_eventsConnections[family] =
               std::make_shared<EventToListenersConnection>();

         return m_eventsConnections[family];
      }

   private:
      EventsConnectionsVector m_eventsConnections;
   };


}