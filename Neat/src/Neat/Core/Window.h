#pragma once

#include <string>
#include <functional>
#include <memory>

#include "Neat/Core/Core.h"
#include "Neat/Events/Event.h"


struct GLFWwindow;


namespace Neat
{
   using eventCallbackFunction = std::function<void(Event&)>;
   struct WindowImpl;

   struct WindowProps
   {
      std::string title;
      Int width;
      Int height;

      WindowProps(const std::string& title = "Neat Engine",
                  Int width = 1280,
                  Int height = 720)
         : title(title), width(width), height(height)
      {
      }
   };

   class Window
   {
   public:
      //Window();
      Window(const WindowProps & props = WindowProps());
      ~Window();

      void onUpdate();

      Int getWidth() const;
      Int getHeight() const;

      void* getNativeWindow() const;

      Bool isMinimized() const;

      // Window attributes
      void setEventCallback(const eventCallbackFunction& callback);
      void setVSync(Bool enabled);
      Bool isSync() const;

   private:
      std::unique_ptr<WindowImpl> data;
   };
}