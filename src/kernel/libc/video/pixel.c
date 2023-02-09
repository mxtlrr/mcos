#include "libc/video/pixel.h"
uint32_t PITCH = 0;

void set_pitch(uint32_t pitch){ PITCH = pitch; }

uint32_t* buffer = 0x0;

void set_fb(uint32_t* addr){
	buffer = addr;
}

uint32_t* get_buffer(){
  return buffer;
}

void putpixel(int x, int y, uint32_t color){
  buffer[x+y*(PITCH)] = color;
}

void plot_mouse_cursor(uint8_t* mouse_ptr, int _x, int _y, uint32_t color){
  int xMax = 16;
  int yMax = 16;
  int differenceX = WIDTH  - _x;
  int differenceY = HEIGHT - _y;

  if (differenceX < 16) xMax = differenceX;
  if (differenceY < 16) yMax = differenceY;

  for (int y = 0; y < yMax; y++){
    for (int x = 0; x < xMax; x++){
      int bit = y * 16 + x;
      int byte = bit / 8;
      if ((mouse_ptr[byte] & (0b10000000 >> (x % 8)))){
        putpixel(_y+y,_x+x, color);
      }
    }
  }
}