#pragma once

#include "video/pixel.h"
#include <stddef.h>
#include <stdint.h>

void putc(char c);
void puts(char* fmt);

void set_fb(uint32_t* addr);