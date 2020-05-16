#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "Neat/Core/Exceptions.h"
#include "Neat/Events/Event.h"


namespace Neat
{
   class EventManager
   {
   public:
      EventManager() = default;
      virtual ~EventManager() = default;

      EventManager(const EventManager&) = delete;
      EventManager& operator = (const EventManager &) = delete;


      template <typename E, typename Receiver>
      void subscribe(Receiver& receiver)
      {
         bool (Receiver::*receive)(const E&) = &Receiver::receive;

         auto signal = getEventSignal(Event<E>::getFamily());

         auto event_callback_wrapper = EventCallback<E>(
            std::bind(receive, &receiver, std::placeholders::_1));
         auto connection = signal->connect(event_callback_wrapper);

         BaseEventReceiver& base = receiver;
         base.m_connections.insert(
            std::make_pair(
               Event<E>::getFamily(),
               std::make_pair(
                  std::weak_ptr<EventSignal>(signal),
                  connection
               )
            )
         );
      }

      template <typename E, typename Receiver>
      void unsubscribe(Receiver& receiver)
      {
         BaseEventReceiver& base = receiver;

         if (base.m_connections.find(Event<E>::getFamily()) 
            == base.m_connections.end())
            throw EventSubscriptionError();

         auto connection_pair = base.m_connections[Event<E>::getFamily()];
         auto connection = connection_pair.second;
         auto signal = connection_pair.first;

         if (!signal.expired())
            signal.lock()->disconnect(connection);

         base.m_connections.erase(Event<E>::getFamily());
      }


      template <typename E>
      void publish(const E& event)
      {
         auto signal = getEventSignal(Event<E>::getFamily());
         signal->emit(&event);
      }

      template <typename E>
      void publish(std::unique_ptr<E> event)
      {
         auto signal = getEventSignal(Event<E>::getFamily());
         signal->emit(event.get());
      }

      template <typename E, typename... Args>
      void publish(Args&&... args)
      {
         E event(std::forward<Args>(args)...);

         auto signal = getEventSignal(Event<E>::getFamily());
         signal->emit(&event);
      }


      std::size_t getNumberOfConnectedReceivers() const
      {
         std::size_t count = 0;
         for (std::shared_ptr<EventSignal> signal : m_eventSignals)
            if (signal)
               count += signal->size();

         return count;
      }

   private:
      std::shared_ptr<EventSignal>& getEventSignal(BaseEvent::Family family)
      {
         if (family >= m_eventSignals.size())
            m_eventSignals.resize(family + 1);
         if (!m_eventSignals[family])
            m_eventSignals[family] = std::make_shared<EventSignal>();

         return m_eventSignals[family];
      }

      template <typename E>
      struct EventCallback
      {
         std::function<bool(const E&)> callback;

         EventCallback(std::function<bool(const E&)> callback)
            : callback(callback) {}

         bool operator()(const void* event)
         {
            return callback(*(static_cast<const E*>(event)));
         }
      };

   private:
      std::vector<std::shared_ptr<EventSignal>> m_eventSignals;
   };
}