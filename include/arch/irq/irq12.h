#pragma once

#include "arch/isr.h"
#include "libc/stdio.h"

#define MOUSE_IRQ 32+12

void mouse_init();
void mouse_callback();

void mouse_wait();
void mouse_timeout();

void mouse_outb(uint8_t val);
uint8_t mouse_read();
void proc_packet();

extern uint8_t mouse_ptr[];