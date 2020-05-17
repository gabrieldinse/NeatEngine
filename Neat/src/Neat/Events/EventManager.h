#pragma once

#include <memory>
#include <vector>
#include <utility>
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
      EventManager& operator=(const EventManager &) = delete;


      template <typename E, typename Receiver>
      void subscribe(Receiver& receiver)
      {
         auto event_subscription = getEventCallback(Event<E>::getFamily());
         auto event_subscription_id = event_subscription->add<E>(receiver);

         BaseEventSubscriber& base = receiver;
         base.m_subscriptions.insert(
            std::make_pair(
               Event<E>::getFamily(),
               std::make_pair(
                  std::weak_ptr<EventSubscription>(event_subscription),
                  event_subscription_id
               )
            )
         );
      }

      template <typename E, typename Receiver>
      void unsubscribe(Receiver& receiver)
      {
         BaseEventSubscriber& base = receiver;

         if (base.m_subscriptions.find(Event<E>::getFamily())
            == base.m_subscriptions.end())
            throw EventSubscriptionError();

         auto event_subscription_pair =
            base.m_subscriptions[Event<E>::getFamily()];
         auto event_subscription_id = event_subscription_pair.second;
         auto event_subscription = event_subscription_pair.first;

         if (!event_subscription.expired())
            event_subscription.lock()->remove(event_subscription_id);

         base.m_subscriptions.erase(Event<E>::getFamily());
      }


      template <typename E>
      void publish(const E& event)
      {
         auto event_subscription = getEventCallback(Event<E>::getFamily());
         event_subscription->publish<E>(event);
      }

      template <typename E>
      void publish(std::unique_ptr<E> event)
      {
         auto event_subscription = getEventCallback(Event<E>::getFamily());
         event_subscription->publish<E>(event);
      }

      template <typename E, typename... Args>
      void publish(Args&&... args)
      {
         auto event_subscription = getEventCallback(Event<E>::getFamily());
         event_subscription->publish<E>(std::forward<Args>(args)...);
      }


      std::size_t getNumberOfSubscribers() const
      {
         std::size_t count = 0;
         for (auto& event_subscription : m_eventSubscriptions)
            if (event_subscription)
               count += event_subscription->size();

         return count;
      }

   private:
      std::shared_ptr<EventSubscription>& getEventCallback(
         BaseEvent::Family family)
      {
         if (family >= m_eventSubscriptions.size())
            m_eventSubscriptions.resize(family + 1);

         if (!m_eventSubscriptions[family])
            m_eventSubscriptions[family] = std::make_shared<EventSubscription>();

         return m_eventSubscriptions[family];
      }

   private:
      std::vector<std::shared_ptr<EventSubscription>> m_eventSubscriptions;
   };


}