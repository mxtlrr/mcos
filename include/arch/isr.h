#pragma once

#include <stddef.h>
#include "libc/stdio.h"
#include "io.h"

typedef struct {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

void exception_handler(void);

void irq_recv(registers_t r);