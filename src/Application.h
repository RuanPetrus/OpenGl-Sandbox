#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Layer.h"

#include <GLFW/glfw3.h>
#include "imgui.h"

namespace App{
  struct ApplicationSpecification
  {
    std::string name = "New App";
    uint32_t width = 1200;
    uint32_t height = 720;
  };

  class Application
  {
  public:
      Application(ApplicationSpecification applicationSpecification);
      ~Application();

      void Run();
      void PushLayer(const std::shared_ptr<Layer>& layer) { m_LayerStack.emplace_back(layer); layer->OnAttach(); }
      void Close();
      float GetTime();

  private:
    void Init();
    void Shutdown();

  private:
    std::vector<std::shared_ptr<Layer>> m_LayerStack;
    GLFWwindow *m_WindowHandle = nullptr;
    ApplicationSpecification m_ApplicationSpecification;
    bool m_Running = false;

    float m_TimeStep = 0.0f;
		float m_FrameTime = 0.0f;
		float m_LastFrameTime = 0.0f;

  };

}
