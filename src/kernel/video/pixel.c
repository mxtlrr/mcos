#include "video/pixel.h"
uint32_t PITCH = 0;

void set_pitch(uint32_t pitch){ PITCH = pitch; }

void putpixel(uint32_t* addr, int x, int y, uint32_t color){
  addr[x+y*(PITCH)] = color;
}