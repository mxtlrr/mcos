DEFAULT_HOST := i386
TARGET			 := myos.bin


CC := i386-elf-gcc
CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
					-Iinclude -g

AS 			:= nasm
ASFLAGS := -f elf32 -g

OUTPUT_DIR  := bin
LINK_SCRIPT := src/linker.ld

override CFILES := $(shell find ./src/kernel -type f)
override OBJS		:= $(shell find ./bin -type f -name '*.o')

all: mcos build_iso

mcos:
	@mkdir -p bin/
	$(AS) $(ASFLAGS) src/boot/boot.s -o $(OUTPUT_DIR)/boot.o
	@$(foreach file, $(CFILES), $(CC) $(CFLAGS) -c $(file) -o bin/$(basename $(notdir $(file))).o; echo "[CC] $(file)";)

	@echo Linking
	$(CC) -T$(LINK_SCRIPT) -o bin/$(TARGET) -ffreestanding -O2 -nostdlib $(OBJS) -lgcc


build_iso: src/boot/grub.cfg
	@mkdir -p isodir/boot/grub
	@cp $(OUTPUT_DIR)/$(TARGET) isodir/boot/$(TARGET)
	@cp $^ isodir/boot/grub/grub.cfg
	@grub-mkrescue -o myos.iso isodir


clean:
	rm -rf $(OUTPUT_DIR) isodir/ myos.iso