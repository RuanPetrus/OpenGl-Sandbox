#include "Render.h"

namespace Render{
  void fill(Canvas canvas, uint32_t color)
  {
    for (uint32_t i = 0; i < canvas.height * canvas.width; i++){
      canvas.data[i] = color;
    }
  }
  
  void fillRetangule(Canvas canvas, 
                  uint32_t start_x, uint32_t start_y, 
                  uint32_t width, uint32_t height, 
                  uint32_t color)
  {
    for (int y = start_y; y < start_y + height && y < canvas.height; y++){
      for (int x = start_x; x < start_x + width && x < canvas.width; x++){
        canvas.data[y * canvas.width + x] = color;
      }
    }
  }

  void fillTriangle(Canvas canvas, 
                    uint32_t x1, uint32_t y1, 
                    uint32_t x2, uint32_t y2, 
                    uint32_t x3, uint32_t y3, 
                    uint32_t color)
  {
    
  }
}
