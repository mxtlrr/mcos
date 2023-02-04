#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multiboot.h"

#include "libc/stdio.h"


void kernel_main(multiboot_info_t* mbd, uint32_t magic){
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) return;
	set_fb((uint32_t*)mbd->framebuffer_addr);

	printf("Hello World\n");

	for(;;) asm("hlt");
}