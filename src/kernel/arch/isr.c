#include "arch/isr.h"

char* mnemonic[] = {
  "#DE",
  "#DB",
  "-",
  "#BP",
  "#OF",
  "#BR",
  "#UD",
  "#NM",
  "#DF",
  "-",
  "#TS",
  "#NP",
  "#SS",
  "#GP",
  "#PF"
};

char* exception[] = {
  "Division Error",
  "Debug",
  "NMI",
  "Breakpoint",
  "Overflow",
  "Bound Range Exceeded",
  "Invalid Opcode",
  "Dev. Not Available",
  "Double Fault",
  "Coprocessor Seg. Overrun",
  "Invalid TSS",
  "Segment Not Present",
  "General Protection Fault",
  "Page Fault"
};


void exception_handler(registers_t r) {
  printf("\n\n%s (%s) triggered!\n",
         exception[r.int_no], mnemonic[r.int_no]);
  printf("Technical details: ");
  set_color(0x189bcc);
  printf("ISR: 0x%x\nErr Code: %d", r.int_no, r.err_code);
  printf(" | EIP at 0x%x\n", r.eip-2);
  // do not exec. code after this
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
  if(r.int_no >= 40) {
    outb(0xA0, 0x20);
  }
  outb(0x20, 0x20);
  if(handlers[r.int_no] != 0){
    // call handler
    isr_t handler = handlers[r.int_no];
    handler(r);
  }
}
