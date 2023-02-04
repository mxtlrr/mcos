[org 0x7c00]
[bits 16]

start:
	jmp .skip_bpb
  nop

  .bpb:
    times 3-($-$$) db 0
    .bpb_oem_id:            db "MCOS     "
    .bpb_sector_size:       dw 512
    .bpb_sects_per_cluster: db 0
    .bpb_reserved_sects:    dw 0
    .bpb_fat_count:         db 0
    .bpb_root_dir_entries:  dw 0
    .bpb_sector_count:      dw 0
    .bpb_media_type:        db 0
    .bpb_sects_per_fat:     dw 0
    .bpb_sects_per_track:   dw 18
    .bpb_heads_count:       dw 2
    .bpb_hidden_sects:      dd 0
    .bpb_sector_count_big:  dd 0
    .bpb_drive_num:         db 0
    .bpb_reserved:          db 0
    .bpb_signature:         db 0
    .bpb_volume_id:         dd 0
    .bpb_volume_label:      db "MCOS       "
    .bpb_filesystem_type:   times 8 db 0

	.skip_bpb:
		cli
		cld
		jmp .startup



  .startup:
    cli ;; disable interrupts
    ;; segment descriptors need to be set to zero
    ;; there's no guarantee that's what they really
    ;; are
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax

    ;; Setup stack ptr to point at 7c00h
    mov sp, 0x7c00
    mov bp, sp  ;; bp → 0x7c00

    ;; read more info from the disk
    mov ah, 0x02
    mov al, 0x3b  ;; 59 sectors
    mov ch, 0x00
    mov cl, 0x02
    mov dh, 0x00
    
    xor bx, bx
    mov es, bx
    mov bx, 0x502
    int 0x13
    jc error

    ;; enable A20,
    ;; giving us access to all memory
    call enable_a20

    jmp $

jmp $

;; fast A20
enable_a20:
  in al,  0x92
  or al,  0x02
  out 0x92, al
  ret

error:
  jmp $

times 510-($-$$) db 0
dw 0xaa55