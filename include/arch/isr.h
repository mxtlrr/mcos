#pragma once

#include <stddef.h>
#include "libc/stdio.h"
#include "io.h"

typedef struct {
  uint32_t ds;
  uint32_t edi, esi, ebp, useless, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

void exception_handler(registers_t r);
typedef void (*isr_t)(registers_t);

void register_int(uint8_t INT, isr_t callback);

void irq_recv(registers_t r);


void test(registers_t r);
void fjdka(uint32_t frequency);