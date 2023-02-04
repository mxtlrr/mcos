#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"

#include "libc/stdio.h"


void kernel_main(multiboot_info_t* mbd, uint32_t magic){
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) return;
	uint32_t* addr = (uint32_t*)mbd->framebuffer_addr;

	putc(addr, 'h', 0, 0);
	putc(addr, 'e', 8, 0);
	putc(addr, 'e', 0, 8);

	for(;;) asm("hlt");
}