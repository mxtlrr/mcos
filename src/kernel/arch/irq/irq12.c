#include "arch/irq/irq12.h"

void mouse_callback(){
  uint8_t mouseData = inb(0x60);
  printf("m");
}

void mouse_wait(){
  uint64_t timeout = 100000;
  while(timeout--){
    if((inb(0x64) & 0b10) == 0) return;
  }
}

void mouse_timeout(){
  uint64_t timeout = 100000;
  while(timeout--){
    if(inb(0x64) & 0b1) return;
  }
}

void mouse_outb(uint8_t val){
  mouse_wait();
  outb(0x64, 0xd4);
  mouse_wait();
  outb(0x60, val);
}

uint8_t mouse_read(){
  mouse_timeout();
  return inb(0x60);
}

void mouse_init(){
  register_int(MOUSE_IRQ, mouse_callback);

  outb(0x64, 0xa8); // enable aux. dev (mouse)
  mouse_wait();
  outb(0x64, 0x20); // let's send a command to the mouse 
  mouse_timeout(); // wait for input

  uint8_t status = inb(0x60);
  status |= 0b10; // 2nd bit set
  mouse_wait();

  outb(0x64, 0x60); // cmd => mouse
  mouse_wait();

  outb(0x60, status); // send correct bit in "compaq" status byte


  // let's use default settings
  mouse_outb(0xf6);
  mouse_read();

  mouse_outb(0xf4);
  mouse_read();
}