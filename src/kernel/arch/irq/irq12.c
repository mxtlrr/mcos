#include "arch/irq/irq12.h"
#include <stdbool.h>


uint8_t mouse_ptr[] = {
  0b11100000, 0b00000000, 
  0b11000000, 0b00000000, 
  0b10000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000
};


#define left_btn 0b00000001

#define x_sign   0b00010000
#define y_sign   0b00110000

#define x_overflow 0b01000000
#define y_overflow 0b10000000

uint8_t mouse_cycle = 0;
uint8_t mouse_packet[4];
bool packet_ready = false;

uint8_t mouse_x = 0;
uint8_t mouse_y = 0;

void handle_mouse(uint8_t data){
  switch(mouse_cycle){
    case 0:
      if(packet_ready) break;
      if(data & 0b0001000 == 0) break; // incorrect byte
      mouse_packet[0] = data;
      mouse_cycle++;
      break;
    case 1:
      if(packet_ready) break;
      mouse_packet[1] = data;
      mouse_cycle++;
      break;
    case 2:
      if(packet_ready) break;
      mouse_packet[2] = data;
      packet_ready = true;
      mouse_cycle = 0;
      break;
  }
}


void proc_packet(){
  if(!packet_ready) return;
    packet_ready = false;

    bool xNeg, yNeg, xOver, yOver;
    if(mouse_packet[0] & x_sign) xNeg = true;
    else xNeg = false;

    if(mouse_packet[0] & y_sign) yNeg = true;
    else yNeg = false;

    if(mouse_packet[0] & x_overflow) xOver = true;
    else xOver = false;

    if(mouse_packet[0] & y_overflow) yOver = true;
    else yOver = false;

    if(!xNeg){
      mouse_x += mouse_packet[1];
      if(xOver) mouse_x += 255;
    } else {
      mouse_packet[1] = 256 - mouse_packet[1];
      mouse_x -= mouse_packet[1];
      if(xOver) mouse_x -= 255;
    }

    if(!yNeg){
      mouse_y -= mouse_packet[2];
      if(yOver) mouse_y -= 255;
    } else {
      mouse_packet[2] = 256 - mouse_packet[2];
      mouse_y += mouse_packet[2];
      if(yOver) mouse_y += 255;
    }

    if(mouse_x < 0) mouse_x = 0;
    if(mouse_x > WIDTH-8) mouse_x = WIDTH-8;

    if(mouse_y < 0) mouse_y = 0;
    if(mouse_y > HEIGHT-16) mouse_y = HEIGHT-16;

    // plot mouse
    if((mouse_x != 0) || (mouse_y != 0)){
      plot_mouse_cursor(mouse_ptr, mouse_x, 35, 0xff00ff);
      plot_mouse_cursor(mouse_ptr, 128, mouse_y, 0xff00ff);
      
      putpixel(128, mouse_y, 0xff00ff);
    
    }

    packet_ready = false;
}

void mouse_callback(){
  uint8_t mouseData = inb(0x60);
  handle_mouse(mouseData);
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