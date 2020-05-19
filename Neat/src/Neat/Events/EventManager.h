#pragma once

#include <memory>
#include <vector>
#include <utility>
#include <functional>

#include "Neat/Core/Exceptions.h"
#include "Neat/Core/Log.h"
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


      template <typename E, typename Subscriber>
      void subscribe(Subscriber& subscriber)
      {
         auto event_subscription = getSubscription(Event<E>::getFamily());
         auto subscription_id = event_subscription->add<E>(subscriber);

         BaseEventSubscriber& base = subscriber;
         base.m_subscriptions.insert(
            std::make_pair(
               Event<E>::getFamily(),
               std::make_pair(
                  std::weak_ptr<EventSubscription>(event_subscription),
                  subscription_id
               )
            )
         );
      }

      template <typename E, typename Subscriber>
      void unsubscribe(Subscriber& subscriber)
      {
         BaseEventSubscriber& base = subscriber;

         if (base.m_subscriptions.find(Event<E>::getFamily())
            == base.m_subscriptions.end())
            throw EventSubscriptionError();

         auto event_subscription_pair =
            base.m_subscriptions[Event<E>::getFamily()];
         auto subscription_id = event_subscription_pair.second;
         auto event_subscription = event_subscription_pair.first;

         if (!event_subscription.expired())
            event_subscription.lock()->remove(subscription_id);

         base.m_subscriptions.erase(Event<E>::getFamily());
      }


      template <typename E>
      void publish(const E& event)
      {
         auto event_subscription = getSubscription(Event<E>::getFamily());
         event_subscription->publish<E>(event);
      }

      template <typename E>
      void publish(std::unique_ptr<E> event)
      {
         auto event_subscription = getSubscription(Event<E>::getFamily());
         event_subscription->publish<E>(event);
      }

      template <typename E, typename... Args>
      void publish(Args&&... args)
      {
         auto event_subscription = getSubscription(Event<E>::getFamily());
         event_subscription->publish<E>(std::forward<Args>(args)...);
      }


      UInt getNumberOfSubscribers() const
      {
         UInt count = 0;
         for (auto& event_subscription : m_subscriptions)
            if (event_subscription)
               count += event_subscription->size();

         return count;
      }

   private:
      std::shared_ptr<EventSubscription>& getSubscription(
         BaseEvent::Family family)
      {
         if (family >= m_subscriptions.size())
            m_subscriptions.resize(family + 1);

         if (!m_subscriptions[family])
            m_subscriptions[family] = std::make_shared<EventSubscription>();

         return m_subscriptions[family];
      }

   private:
      std::vector<std::shared_ptr<EventSubscription>> m_subscriptions;
   };


}