#include "video/pixel.h"

void putpixel(uint32_t* addr, int x, int y, uint32_t color){
  addr[x*4+y*(PITCH)] = color;
}