#pragma once

#include "video/pixel.h"
#include "libc/string.h"

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

void putc(char c);
void puts(char* fmt);
void printf(char* fmt, ...);

void set_color(uint32_t col);