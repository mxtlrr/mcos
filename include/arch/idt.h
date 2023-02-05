#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "io.h"

typedef struct {
  uint16_t isr_low;     // lower 16 bits
  uint16_t kernel_cs;   // 0x08
  uint8_t  reserved;    // always 0
  uint8_t  attributes;  // type & attributes
  uint16_t isr_high;    // higher 16 bits
}__attribute__((packed)) idt_entry_t;


typedef struct {
  uint16_t limit;
  uint32_t base;
}__attribute__((packed)) idtr_t;


void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
uint32_t idt_init(void);