#include "arch/isr.h"

void exception_handler() {
  set_color(RED);
  printf("\nSomething bad happened\n");
  printf("Exception handler called!\n");
  __asm__ volatile ("cli; hlt"); // Completely hangs the computer
  for(;;);
}

void irq_recv(registers_t r){
  if(r.int_no >= 40)
    outb(0xA0, 0x20);
  outb(0x20, 0x20);
  
  printf("the shitter 400\n");
}