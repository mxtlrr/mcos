#include "arch/i386/gdt.h"

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

// initialize gdt
uint32_t init_gdt(){
  gdt_ptr.limit = (sizeof(gdt_entry_t)*5)-1;
  gdt_ptr.base  = (uint32_t)&gdt_entries;

  // set up descriptors for the usual kernel mode
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9a, GRANULARITY);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, GRANULARITY);

  // user mode
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xfa, 0xcf);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xf2, 0xcf);

  // initialize gdt
  flush_gdt((uint32_t)&gdt_ptr);
  return (uint32_t)&gdt_ptr; // return location of GDTR
}

void gdt_set_gate(int num, uint32_t base, uint32_t limit, 
                  uint8_t access, uint8_t granularity){
	gdt_entries[num].base_low     = (base & 0xFFFF);
	gdt_entries[num].base_middle  = (base >> 16) & 0xFF;
	gdt_entries[num].base_high	  = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low	  = (limit & 0xFFFF);
	gdt_entries[num].granularity  = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= granularity & 0xF0;
	gdt_entries[num].access			  = access;
}