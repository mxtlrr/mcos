#pragma once

#include <stddef.h>
#include "libc/stdio.h"

typedef struct {
	uint32_t start;
	uint32_t ending;
	uint32_t size;
	uint8_t  attributes;
}__attribute__((packed)) block_t;

extern block_t blocks[];

void put_block(block_t block, int index);

uint32_t kmalloc(uint32_t n);
char kfree(uint32_t loc);
