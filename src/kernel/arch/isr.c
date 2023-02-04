#include "arch/isr.h"

void exception_handler() {
  printf("Something bad happened\n");
  __asm__ volatile ("cli; hlt"); // Completely hangs the computer
}