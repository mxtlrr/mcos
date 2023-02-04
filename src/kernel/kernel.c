#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"

#define WIDTH 1024

void kernel_main(multiboot_info_t* mbd, uint32_t f){
	if(f != MULTIBOOT_BOOTLOADER_MAGIC) for(;;);
	int x = 20;
	int y = 40;
	int color = 0x06;


	unsigned char* screen = (unsigned char*)mbd->framebuffer_addr;
	unsigned where = x*4 + y*mbd->framebuffer_pitch;
	screen[where] = color & 255;              // BLUE
	screen[where + 1] = (color >> 8) & 255;   // GREEN
	screen[where + 2] = (color >> 16) & 255;  // RED
  
	for(;;) asm("hlt");
}