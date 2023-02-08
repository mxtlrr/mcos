#include "multiboot.h"
#include "libc/stdio.h"

/* low level stuff */
#include "arch/gdt.h"
#include "arch/idt.h"

#include "arch/isr.h"

/* irqs */
#include "arch/irq/irq0.h"
#include "arch/irq/irq12.h"

void kernel_main(multiboot_info_t* mbd, uint32_t magic){
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) return;
	set_fb((uint32_t*)mbd->framebuffer_addr);
	set_pitch(mbd->framebuffer_pitch);

	printf("Hello World\n");
	uint32_t gdtr = init_gdt()+0x20;
	uint32_t idtr = init_idt()+0x20;
	printf("GDT was loaded at 0x%x\n", gdtr);
	printf("IDT was loaded at 0x%x\n", idtr);

	register_pit(60);
	
	for(;;){
		asm("hlt");
	}
}
