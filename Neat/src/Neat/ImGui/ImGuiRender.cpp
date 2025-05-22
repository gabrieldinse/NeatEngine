#include "Neat/Core/Application.h"
#include "Neat/ImGui/ImGuiRender.h"


#include <imgui.h> // need to be before the next two includes
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace Neat
{
   void ImGuiRender::init()
   {
      // Setup Dear ImGui context
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      auto& io = ImGui::GetIO();
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;        // Enable Gamepad Controls
      io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
      io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
      // TODO check these flags
      //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
      //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

      // Setup Dear ImGui style
      ImGui::StyleColorsDark();

      // When viewports are enabled we tweak WindowRounding/WindowBg 
      // so platform windows can look identical to regular ones.
      auto& style = ImGui::GetStyle();
      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
      {
         style.WindowRounding = 0.0f;
         style.Colors[ImGuiCol_WindowBg].w = 1.0f;
      }

      auto& application = Application::get();
      auto window = static_cast<GLFWwindow*>(
         application.getWindow().getNativeWindow());

      // Setup Platform/Renderer bindings
      ImGui_ImplGlfw_InitForOpenGL(window, true);
      ImGui_ImplOpenGL3_Init("#version 410");
   }

   void ImGuiRender::shutdown()
   {
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();
   }

   void ImGuiRender::begin()
   {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
   }

   void ImGuiRender::end()
   {
      auto& io = ImGui::GetIO();
      auto& app = Application::get();
      io.DisplaySize = ImVec2(
      (float)app.getWindow().getWidth(),
         (float)app.getWindow().getHeight());

      // Rendering
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
      {
         auto backup_current_context = glfwGetCurrentContext();
         ImGui::UpdatePlatformWindows();
         ImGui::RenderPlatformWindowsDefault();
         glfwMakeContextCurrent(backup_current_context);
      }
   }
}