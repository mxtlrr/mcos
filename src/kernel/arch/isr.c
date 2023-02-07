#include "arch/isr.h"

void exception_handler() {
  set_color(RED);
  printf("\nSomething bad happened\n");
  printf("Exception handler called!\n");
  __asm__ volatile ("cli; hlt"); // Completely hangs the computer
  for(;;);
}

/*********************/
isr_t handlers[256];
void register_int(uint8_t INT, isr_t callback){
  printf("IRQ #%d registered\n", INT-32);
  handlers[INT] = callback;
}


void irq_recv(registers_t r){
  if(handlers[r.int_no] != 0){
    // call handler
    isr_t handler = handlers[r.int_no];
    handler(r);

    if(r.int_no >= 40) {
      outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
  }
}
