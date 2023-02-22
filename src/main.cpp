#include "Application.h"
#include "Image.h"

class ExampleLayer : public App::Layer
{
public:
  void OnUIRender() override
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

private:
  void Render()
  {
    if (!m_Image || m_ViewPortHeight != m_Image->GetHeight() || m_ViewPortWidth != m_Image->GetWidth()){
      m_Image = std::make_shared<Image>(m_ViewPortWidth, m_ViewPortHeight, nullptr);
      delete[] m_ImageData;
      m_ImageData = new uint32_t[m_ViewPortHeight * m_ViewPortWidth];
    }

    for (uint32_t i = 0; i < m_ViewPortHeight * m_ViewPortWidth; i++){
        m_ImageData[i] = 0xFFFF00FF;
      }
    m_Image->SetData(m_ImageData);
  }
private:
    uint32_t m_ViewPortWidth = 0;
    uint32_t m_ViewPortHeight = 0;

    uint32_t *m_ImageData = nullptr;

    std::shared_ptr<Image> m_Image;
};

int main(){
  App::ApplicationSpecification spec = App::ApplicationSpecification();
  spec.name = "Example App";
  App::Application *app = new App::Application(spec);
  std::shared_ptr<ExampleLayer> exampleLayer = std::make_shared<ExampleLayer>();
  
  app->PushLayer(exampleLayer);
  app->Run();

}
