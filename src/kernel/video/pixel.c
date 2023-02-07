#include "video/pixel.h"
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