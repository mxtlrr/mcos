#include "arch/irq/irq0.h"

uint32_t tick = 0;
void pit_callback(){
	tick++;
  printf("%d ", tick);
  outb(0x20, 0x20);
}

void register_pit(uint32_t freq){
  register_int(32, pit_callback);

	uint32_t divisor = 1193180/freq;

	// Send the command byte.
	outb(0x43, 0x36);

	// Divisor has to be sent byte-wise, so split here into upper/lower bytes.
	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)((divisor>>8) & 0xFF);

	// Send the frequency divisor.
	outb(0x40, l);
	outb(0x40, h);
}