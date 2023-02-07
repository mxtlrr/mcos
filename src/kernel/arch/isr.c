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

uint32_t tick = 0;
void test(registers_t r){
  tick++;
  printf("ok\n");
}

void fjdka(uint32_t frequency){
  register_int(32, test);

   uint32_t divisor = 1193180 / frequency;

   // Send the command byte.
   outb(0x43, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   uint8_t l = (uint8_t)(divisor & 0xFF);
   uint8_t h = (uint8_t)((divisor>>8) & 0xFF);

   // Send the frequency divisor.
   outb(0x40, l);
   outb(0x40, h);
}