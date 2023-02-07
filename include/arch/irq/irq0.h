/* Keyboard interrupt */
#pragma once

#include "arch/isr.h"

void register_pit(uint32_t freq);
void pit_callback();