#pragma once

#include <stddef.h>
#include "libc/stdio.h"
#include "io.h"

enum IRQs {
  IRQ0 = 32,
  IRQ1 = 33,
  IRQ2 = 34,
  IRQ3 = 35,
  IRQ4 = 36,
  IRQ5 = 37,
  IRQ6 = 38,
  IRQ7 = 39,
  IRQ8 = 40,
  IRQ9 = 41,
  IRQ10 = 42,
  IRQ11 = 43,
  IRQ12 = 44,
  IRQ13 = 45,
  IRQ14 = 46,
  IRQ15 = 47
};

typedef struct {
  uint32_t ds;
  uint32_t edi, esi, ebp, useless, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

void exception_handler(registers_t r);
typedef void (*isr_t)();

void register_int(uint8_t INT, isr_t callback);

void irq_recv(registers_t r);
