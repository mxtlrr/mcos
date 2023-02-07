#pragma once

#include <stddef.h>
#include <stdint.h>

#include "arch/irq/irq12.h"
#define RED   0xff0000
#define GREEN 0x00ff00
#define BLUE  0x0000ff

#define WIDTH  1024
#define HEIGHT  768

void putpixel(int x, int y, uint32_t color);

void set_pitch(uint32_t pitch);
void set_fb(uint32_t* addr);
uint32_t* get_buffer();

void plot_mouse_cursor(uint8_t* mouse_ptr, int _x, int _y, uint32_t color);