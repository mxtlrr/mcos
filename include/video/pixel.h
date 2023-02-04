#pragma once

#include <stddef.h>
#include <stdint.h>

#define RED   0xff0000
#define GREEN 0x00ff00
#define BLUE  0x0000ff

#define WIDTH  1024
#define HEIGHT  768

#define PITCH 4096

void putpixel(uint32_t* addr, int x, int y, uint32_t color);