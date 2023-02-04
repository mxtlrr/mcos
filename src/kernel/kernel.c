#include "multiboot.h"
#include "libc/stdio.h"

/* arch */
#include "arch/gdt.h"


void kernel_main(multiboot_info_t* mbd, uint32_t magic){
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) return;
	set_fb((uint32_t*)mbd->framebuffer_addr);

	printf("Hello World\n");
	init_gdt();

	for(;;) asm("hlt");
}