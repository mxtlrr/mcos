#include "multiboot.h"
#include "libc/stdio.h"

/* low level stuff */
#include "arch/gdt.h"
#include "arch/idt.h"


void kernel_main(multiboot_info_t* mbd, uint32_t magic){
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) return;
	set_fb((uint32_t*)mbd->framebuffer_addr);
	set_pitch(mbd->framebuffer_pitch);

	printf("Hello World\n");
	uint32_t gdtr = init_gdt()+0x20;
	uint32_t idtr = idt_init()+0x10;
	printf("GDT was loaded at 0x%x\n", gdtr);
	printf("IDT was loaded at 0x%x\n", idtr);

	asm("sti");
	for(;;) asm("hlt");
}