#include "arch/irq/irq1.h"

#define KBD_IN  0x60
#define KBD_ACK 0xfa

// US Query keymap
// Credit: bran's kernel development tutorial
unsigned char kbdus[128] = {
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
	0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
	0,	/* Alt */
  ' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	0,	/* Up Arrow */
	0,	/* Page Up */
	'-',
	0,	/* Left Arrow */
	0,
	0,	/* Right Arrow */
	'+',
	0,	/* 79 - End key*/
	0,	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};	

void init_kbd(){
	register_int(IRQ1, kbd_callback);

	outb(0xf0, 0x00); // get scancode
	uint8_t scan = inb(0x60);
	if(scan == KBD_ACK){
		if(scan != 0x43){ // probably hex
			// set to scan code set 1
			outb(0xf0, 0x01);
			printf("Originally scan code set %d, changed to 1.\n\n", scan);
		} else {
			printf("Scan: %d (0x%x)\n", scan, scan);
		}
	} else {
		printf("Could not set scancode set (wanted 0xFA, got 0x%x instead)\n\n",
						scan);
	}
}

void kbd_callback(){
	uint8_t untreated = inb(0x60);
	if(untreated & 0x80){
		// shift alt or control
	} else {
		printf("%c", kbdus[untreated]);
	}
}