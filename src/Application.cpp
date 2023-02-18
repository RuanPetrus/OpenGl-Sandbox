#include <memory>

#include "Image.h"
#include "Render.h"

#include "imgui.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

class Application
{
public:
  Application(){}
  void Run()
  {
    ImGui::Begin("Settings");
    
    if (ImGui::Button("Render"))
      Render();

    ImGui::End();

    ImGui::Begin("Viewport");                          // Create a window called "Hello, world!" and append into it.
    m_ViewPortWidth = ImGui::GetContentRegionAvail().x;                                                         
    m_ViewPortHeight = ImGui::GetContentRegionAvail().y;                                                         
                                                                                                                
    if (m_Image)
      ImGui::Image(m_Image->GetImageDescriptor(), 
                   ImVec2(m_Image->GetWidth(), m_Image->GetHeight()));
                                                                                                                                                     
    ImGui::End();
  }
  void Render()
  {
    if (!m_Image || m_ViewPortHeight != m_Image->GetHeight() || m_ViewPortWidth != m_Image->GetWidth()){
      m_Image = std::make_shared<Image>(m_ViewPortWidth, m_ViewPortHeight, nullptr);
      delete[] m_ImageData;
      m_ImageData = new uint32_t[m_ViewPortHeight * m_ViewPortWidth];
    }

    Render::Canvas canvas;
    canvas.data = m_ImageData;
    canvas.width = m_ViewPortWidth;
    canvas.height = m_ViewPortHeight;

    Render::fill(canvas, 0xff0000ff);
    Render::fillRetangule(
        canvas, 
        canvas.width/4, canvas.height/4, 
        canvas.width/2, canvas.height/2, 
        0xffff0000);

    m_Image->SetData(m_ImageData);
  }
private:
    uint32_t m_ViewPortWidth = 0;
    uint32_t m_ViewPortHeight = 0;

    uint32_t *m_ImageData = nullptr;

    std::shared_ptr<Image> m_Image;
};

