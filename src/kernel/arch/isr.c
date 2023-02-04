#include "arch/isr.h"

void exception_handler() {
  set_color(RED);
  printf("\nSomething bad happened\n");
  printf("Exception handler called!\n");
  __asm__ volatile ("cli; hlt"); // Completely hangs the computer
}