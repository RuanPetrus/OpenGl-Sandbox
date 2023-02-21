#include "Application.h"

#include <stdio.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

namespace App{
  Application::Application(ApplicationSpecification applicationSpecification)
  : m_ApplicationSpecification(applicationSpecification)
  {
    Init();
  }
  Application::~Application()
  {
    Shutdown();
  }
  void Application::Init()
  {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
      fprintf(stderr, "Could not Initialize GLFW!\n");

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Create window with graphics context
    m_WindowHandle = glfwCreateWindow(m_ApplicationSpecification.width, m_ApplicationSpecification.height, 
                                       m_ApplicationSpecification.name.c_str(),
                                       NULL, NULL);
    if (m_WindowHandle == NULL)
      fprintf(stderr, "Could not create GLFW window\n");

    glfwMakeContextCurrent(m_WindowHandle);
    glfwSwapInterval(1); // Enable vsync
  
    // Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;
  
    // Setup Dear ImGui style
		ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_WindowHandle, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    m_Running = true;

  }
  void Application::Shutdown()
  {
    for (auto& layer: m_LayerStack)
      layer->OnDetach();
    
    m_LayerStack.clear();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_WindowHandle);
    glfwTerminate();

    m_Running = false;
  }

  void Application::Run()
  {
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    m_Running = true;
		ImGuiIO& io = ImGui::GetIO();

    while (!glfwWindowShouldClose(m_WindowHandle) && m_Running){

      glfwPollEvents();

      for (auto& layer: m_LayerStack)
        layer->OnUpdate(m_TimeStep);

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
      ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

      for (auto& layer: m_LayerStack)
        layer->OnUIRender();

      // Rendering
      ImGui::Render();
      int display_w, display_h;
      glfwGetFramebufferSize(m_WindowHandle, &display_w, &display_h);
      glViewport(0, 0, display_w, display_h);
      glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
      glClear(GL_COLOR_BUFFER_BIT);
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
      //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
      {
          GLFWwindow* backup_current_context = glfwGetCurrentContext();
          ImGui::UpdatePlatformWindows();
          ImGui::RenderPlatformWindowsDefault();
          glfwMakeContextCurrent(backup_current_context);
      }

      glfwSwapBuffers(m_WindowHandle);

      // Calculate delta_time
      float time = GetTime();
      m_FrameTime = time - m_LastFrameTime;
      m_TimeStep = std::min(m_FrameTime, 0.0333f);
      m_LastFrameTime = time;
    }
  }

  float Application::GetTime(){
    return (float)glfwGetTime();
  }
    
}
