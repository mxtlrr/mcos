MBALIGN  equ  1 << 0            ;; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ;; provide memory map
VMODE    equ  1 << 2            ;; video mode
MBFLAGS  equ  MBALIGN | MEMINFO ;; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ;; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + MBFLAGS) ;; checksum

WIDTH_FB equ 640
HEIGHT_F equ 480
DEPTH    equ  32

section .multiboot
align 4
  dd MAGIC
  dd MBFLAGS
  dd CHECKSUM

  ;; Padding
  dd 0
  dd 0
  dd 0
  dd 0
  dd 0

  ;; Framebuffer information
  dd 0         ;; Hey, give me a framebuffer!
  dd WIDTH_FB  ;; Width
  dd HEIGHT_F
  dd DEPTH

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top

	extern kernel_main
	call kernel_main

	cli
.hang:	hlt
	jmp .hang
.end: