#include <stdint.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

class Image
{
public:
  Image(uint32_t width, uint32_t weight, const uint32_t *data);

  void SetData(const uint32_t *data);

  void *GetImageDescriptor() { return (void*)(intptr_t) m_texture; }
  uint32_t GetWidth() const { return m_Width; }
  uint32_t GetHeight() const { return m_Height; }

private:
  GLuint m_texture = 0;
  uint32_t m_Width = 0;
  uint32_t m_Height = 0;
};
