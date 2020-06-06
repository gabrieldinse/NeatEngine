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


   using EventCallback = std::function<bool(const void*)>;

   enum class EventPriority : UIntShort
   {
      Lowest, Low, High, Normal, Highest
   };

   bool operator<(EventPriority priorityA, EventPriority priorityB);
   bool operator==(EventPriority priorityA, EventPriority priorityB);


   // ---------------------------------------------------------------------- //
   // EventToListenersConnection ------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class EventToListenersConnection
   {
   public:
      // EventCallbackElement -------------------------------------------------
      struct EventCallbackElement
      {
         
         EventCallbackElement(const std::shared_ptr<EventCallback>& callback,
            EventPriority priority, bool ignoreIfHandled)
            : callback(callback)
            , priority(priority)
            , ignoreIfHandled(ignoreIfHandled) {}

         std::shared_ptr<EventCallback> callback;
         EventPriority priority;
         bool ignoreIfHandled;
      };
      // ----------------------------------------------------------------------

   public:
      EventToListenersConnection() = default;

      template <typename E, typename Listener>
      std::size_t addListener(Listener& listener, EventPriority priority,
         bool ignoreIfHandled)
      {
         bool (Listener::* listenEvent)(const E&) = &Listener::listenEvent;

         auto callback = EventCallbackWrapper<E>(
            std::bind(listenEvent, &listener, std::placeholders::_1));

         auto callback_element = EventCallbackElement(
            std::make_shared<EventCallback>(callback), priority,
            ignoreIfHandled);

         m_callbackElements.insert(
            std::lower_bound(
               m_callbackElements.begin(),
               m_callbackElements.end(),
               priority,
               [](const EventCallbackElement& element, EventPriority priority)
               {
                  return !(element.priority < priority);
               }
            ),
            callback_element
         );

         return (std::size_t)m_callbackElements.back().callback.get();
      }

      void removeListener(std::size_t id)
      {
         m_callbackElements.remove_if(
            [id](const EventCallbackElement& callbackElement)
            {
               return (std::size_t)callbackElement.callback.get() == id;
            });
      }

      template <typename E>
      void publishEvent(const E& event)
      {
         executeCallbacks(&event);
      }

      template <typename E>
      void publishEvent(std::unique_ptr<E> event)
      {
         executeCallbacks(event.get());
      }

      template <typename E, typename... Args>
      void publishEvent(Args&&... args)
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
      std::list<EventCallbackElement> m_callbackElements;
   };


   // ---------------------------------------------------------------------- //
   // BaseEventListener ---------------------------------------------------- //
   // ---------------------------------------------------------------------- //
   class BaseEventListener
   {
   public:
      using ConnectedEventsMap = std::unordered_map<
         BaseEvent::Family,
         std::pair<std::weak_ptr<EventToListenersConnection>, std::size_t>>;

   public:
      BaseEventListener::~BaseEventListener()
      {
         for (auto&& [family, connection_pair] : m_connectedEvents)
         {
            auto&& [connection, connection_id] = connection_pair;
            if (!connection.expired())
               connection.lock()->removeListener(connection_id);
         }
      }

      UInt BaseEventListener::getNumberOfConnectedSignals() const
      {
         UInt count = 0;
         for (auto&& [family, connection_pair] : m_connectedEvents)
         {
            auto&& [connection, connection_id] = connection_pair;
            if (!connection.expired())
               ++count;
         }
            
         return count;
      }

   private:
      friend class EventManager;

      ConnectedEventsMap m_connectedEvents;
   };


   // ---------------------------------------------------------------------- //
   // EventListener ------------------------------------------------------ //
   // ---------------------------------------------------------------------- //
   template <typename Derived>
   struct EventListener : public BaseEventListener
   {
      virtual ~EventListener() {}
   };
}