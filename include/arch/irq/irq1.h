#pragma once

#include <arch/isr.h>
#include <libc/stdio.h>

void init_kbd(); // basically just the register
                 // interrupt handler but yeah,
                 // this will be expanded soon

void kbd_callback(); // every single IRQ call
                     // (e.g. when a keyboard key
                     // gets pressed) will be routed
                     // through this function
