#pragma once

#include <unordered_map>
#include <utility>
#include <memory>
#include <functional>
#include <list>
#include <algorithm>

#include "Neat/Events/Event.h"


namespace Neat
{
   class EventManager;


   // ---------------------------------------------------------------------- //
   // CallbackElement ------------------------------------------------------ //
   // ---------------------------------------------------------------------- //
   using EventCallback = std::function<bool(const void*)>;

   enum class EventPriority : UIntShort
   {
      Lowest, Low, High, Normal, Highest
   };

   bool operator<(EventPriority priorityA, EventPriority priorityB);
   bool operator==(EventPriority priorityA, EventPriority priorityB);


   struct CallbackElement
   {
      CallbackElement(const std::shared_ptr<EventCallback>& callback,
         EventPriority priority, bool ignoreIfHandled)
         : callback(callback)
         , priority(priority)
         , ignoreIfHandled(ignoreIfHandled) {}

      std::shared_ptr<EventCallback> callback;
      EventPriority priority;
      bool ignoreIfHandled;
   };


   // ---------------------------------------------------------------------- //
   // EventSubscriberGroup ------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class EventSubscriberGroup
   {
   public:
      EventSubscriberGroup() = default;

      template <typename E, typename Subscriber>
      std::size_t addSubscriber(Subscriber& subscriber, EventPriority priority,
         bool ignoreIfHandled)
      {
         bool (Subscriber:: * receive)(const E&) = &Subscriber::receive;

         auto callback = EventCallbackWrapper<E>(
            std::bind(receive, &subscriber, std::placeholders::_1));

         auto callback_element = CallbackElement(
            std::make_shared<EventCallback>(callback), priority,
            ignoreIfHandled);

         m_callbackElements.insert(
            std::lower_bound(
               m_callbackElements.begin(),
               m_callbackElements.end(),
               priority,
               [](const CallbackElement& element, EventPriority priority)
               {
                  return !(element.priority < priority);
               }
            ),
            callback_element
         );

         return (std::size_t)m_callbackElements.back().callback.get();
      }

      void removeSubscriber(std::size_t id)
      {
         m_callbackElements.remove_if(
            [id](const CallbackElement& callbackElement)
            {
               return (std::size_t)callbackElement.callback.get() == id;
            });
      }

      template <typename E>
      void publish(const E& event)
      {
         executeCallbacks(&event);
      }

      template <typename E>
      void publish(std::unique_ptr<E> event)
      {
         executeCallbacks(event.get());
      }

      template <typename E, typename... Args>
      void publish(Args&&... args)
      {
         E event(std::forward<Args>(args)...);
         executeCallbacks(&event);
      }


      std::size_t size() const { return m_callbackElements.size(); }

   private:
      template <typename E>
      struct EventCallbackWrapper
      {
         std::function<bool(const E&)> callback;

         EventCallbackWrapper(std::function<bool(const E&)> callback)
            : callback(callback) {}

         bool operator()(const void* event)
         {
            return callback(*(static_cast<const E*>(event)));
         }
      };

      void executeCallbacks(const void* event)
      {
         bool handled = false;
         for (auto& callback_element : m_callbackElements)
            if (callback_element.callback != nullptr &&
               (callback_element.ignoreIfHandled || !handled))
            {
               handled |= (*callback_element.callback)(event);
            }
      }

   private:
      std::list<CallbackElement> m_callbackElements;
   };


   // ---------------------------------------------------------------------- //
   // BaseEventSubscriber -------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class BaseEventSubscriber
   {
   public:
      BaseEventSubscriber::~BaseEventSubscriber()
      {
         for (auto& subscription_pair : m_subscriptionsMap)
         {
            auto& subscription = subscription_pair.second.first;
            if (!subscription.expired())
               subscription.lock()->removeSubscriber(
                  subscription_pair.second.second);
         }
      }

      UInt BaseEventSubscriber::getNumberOfConnectedSignals() const
      {
         UInt count = 0;
         for (auto& subscription_pair : m_subscriptionsMap)
            if (!subscription_pair.second.first.expired())
               ++count;

         return count;
      }

   private:
      friend class EventManager;

      std::unordered_map<
         BaseEvent::Family,
         std::pair<std::weak_ptr<EventSubscriberGroup>, std::size_t>
      > m_subscriptionsMap;
   };


   // ---------------------------------------------------------------------- //
   // EventSubscriber ------------------------------------------------------ //
   // ---------------------------------------------------------------------- //
   template <typename Derived>
   struct EventSubscriber : public BaseEventSubscriber
   {
      virtual ~EventSubscriber() {}
   };
}