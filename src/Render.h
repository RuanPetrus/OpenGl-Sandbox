#include "stdint.h"

namespace Render {
  struct Canvas{
    uint32_t *data;
    uint32_t width;
    uint32_t height;
  };

  void fill(Canvas canvas, uint32_t color);
  void fillRetangule(Canvas canvas, uint32_t start_x, uint32_t start_y, uint32_t width, uint32_t height, uint32_t color);
  void fillTriangle(Canvas canvas, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, uint32_t color);
}
