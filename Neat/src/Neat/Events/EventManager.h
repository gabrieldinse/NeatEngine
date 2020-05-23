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
         auto subscriber_group = getSubscriberGroup(Event<E>::getFamily());
         auto subscription_id = subscriber_group->addSubscriber<E>(subscriber);

         BaseEventSubscriber& base = subscriber;
         base.m_subscriptions_map.insert(
            std::make_pair(
               Event<E>::getFamily(),
               std::make_pair(
                  std::weak_ptr<EventSubscriberGroup>(subscriber_group),
                  subscription_id
               )
            )
         );
      }

      template <typename E, typename Subscriber>
      void unsubscribe(Subscriber& subscriber)
      {
         BaseEventSubscriber& base = subscriber;

         if (base.m_subscriptions_map.find(Event<E>::getFamily())
            == base.m_subscriptions_map.end())
            throw EventSubscriptionError();

         auto event_subscription_pair =
            base.m_subscriptions_map[Event<E>::getFamily()];
         auto subscription_id = event_subscription_pair.second;
         auto subscriber_group = event_subscription_pair.first;

         if (!subscriber_group.expired())
            subscriber_group.lock()->removeSubscriber(subscription_id);

         base.m_subscriptions_map.erase(Event<E>::getFamily());
      }


      template <typename E>
      void publish(const E& event)
      {
         auto subscriber_group = getSubscriberGroup(Event<E>::getFamily());
         subscriber_group->publish<E>(event);
      }

      template <typename E>
      void publish(std::unique_ptr<E> event)
      {
         auto subscriber_group = getSubscriberGroup(Event<E>::getFamily());
         subscriber_group->publish<E>(event);
      }

      template <typename E, typename... Args>
      void publish(Args&&... args)
      {
         auto subscriber_group = getSubscriberGroup(Event<E>::getFamily());
         subscriber_group->publish<E>(std::forward<Args>(args)...);
      }


      UInt getNumberOfSubscribers() const
      {
         UInt count = 0;
         for (auto& subscriber_group : m_subscriberGroups)
            if (subscriber_group)
               count += subscriber_group->size();

         return count;
      }

   private:
      std::shared_ptr<EventSubscriberGroup>& getSubscriberGroup(
         BaseEvent::Family family)
      {
         if (family >= m_subscriberGroups.size())
            m_subscriberGroups.resize((std::size_t)family + 1);

         if (!m_subscriberGroups[family])
            m_subscriberGroups[family] = std::make_shared<EventSubscriberGroup>();

         return m_subscriberGroups[family];
      }

   private:
      std::vector<std::shared_ptr<EventSubscriberGroup>> m_subscriberGroups;
   };


}