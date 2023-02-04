#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"
#include "video/pixel.h"


void kernel_main(multiboot_info_t* mbd, uint32_t magic){
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) return;
	uint32_t* addr = (uint32_t*)mbd->framebuffer_addr;

	for(int i = 15; i != 31; i++)
		putpixel(addr, i, 27, GREEN);
  
	for(;;) asm("hlt");
}