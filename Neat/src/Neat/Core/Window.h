#pragma once

#include <string>
#include <functional>
#include <memory>

#include "Neat/Core/Core.h"
#include "Neat/Core/Types.h"
#include "Neat/Events/EventManager.h"


struct GLFWwindow;


namespace Neat
{
   class Application;


   class Window
   {
   public:
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

   public:
      Window(EventManager& eventManager,
         const WindowProps& props = WindowProps());
      ~Window();

      void onUpdate();

      Int getWidth() const;
      Int getHeight() const;

      void* getNativeWindow() const;

      bool isMinimized() const;

      // Window attributes
      void setVSync(bool enabled);
      bool isSync() const;

   private:
      std::unique_ptr<WindowImpl> m_data;
   };
}