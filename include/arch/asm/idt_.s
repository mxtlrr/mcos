KERNEL_SS equ 0x10


%macro isr_err_stub 1
isr_stub_%+%1:
  call exception_handler
  iret 
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
  call exception_handler
  iret
%endmacro


extern exception_handler
isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31


global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    32 
  dd isr_stub_%+i
%assign i i+1 
%endrep


;; %1 -> IRQ # (e.g. 00-15)
;; %2 -> ISR # (e.g. 32-47)
%macro IRQ 2
  global irq_stub_%1
  irq_stub_%1:
    cli ;; clear interrupts before we just to interrupt handler
    push byte 0
    push byte %2  ;; recognize that this is an IRQ
    jmp common_hdlr_irq
%endmacro


IRQ 0,  32
IRQ 1,  33
IRQ 2,  34
IRQ 3,  35
IRQ 4,  36
IRQ 5,  37
IRQ 6,  38
IRQ 7,  39
IRQ 8,  40
IRQ 9,  41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

global irq_stub_table
irq_stub_table:
%assign j 0
%rep 15
  dd irq_stub_%+j
%assign j j+1
%endrep

[extern irq_recv]
common_hdlr_irq:
	pusha

	mov ax, ds
	push eax

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call irq_recv

	pop ebx
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx

	popa
	add esp, 8
	sti
	iretd