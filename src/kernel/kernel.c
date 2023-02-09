#include "multiboot.h"
#include "libc/stdio.h"

/* low level stuff */
#include "arch/i386/gdt.h"
#include "arch/i386/idt.h"

#include "arch/i386/isr.h"

/* irqs */
#include "arch/i386/irq/irq0.h"
#include "arch/i386/irq/irq1.h"

void kernel_main(multiboot_info_t* mbd, uint32_t magic){
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC
		&& !(mbd->flags >> 6 & 0x1)) return;
	set_fb((uint32_t*)mbd->framebuffer_addr);
	set_pitch(mbd->framebuffer_pitch);

	uint16_t total = 0;
	uint8_t lowmem, highmem = 0;
	outb(0x70, 0x30);
	lowmem = inb(0x71);
	outb(0x70, 0x31);
	highmem = inb(0x71);

	total = lowmem|highmem << 8;
	printf("From CMOS:\nLow Memory: %d\nHigh Memory: %d\nTotal: %d\n",
		lowmem, highmem, total);


	printf("\nFrom GRUB:\n");
	for(int i = 0; i < mbd->mmap_length; i+= sizeof(multiboot_memory_map_t)){
		multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*)mbd->mmap_addr+i;

		printf("Starts at: 0x%x (high %x) | 0x%x bytes long | Size: 0x%x | Type: %d\n",
					mmmt->addr_low, mmmt->addr_high, mmmt->len_low, mmmt->size, mmmt->type);
	}


	printf("\nHello World\n");
	uint32_t gdtr = init_gdt()+0x20;
	uint32_t idtr = init_idt()+0x20;
	printf("GDT was loaded at 0x%x\n", gdtr);
	printf("IDT was loaded at 0x%x\n", idtr);

	register_pit(60);
	init_kbd();
	
	for(;;){
		asm("hlt");
	}
}
