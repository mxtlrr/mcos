HOST := i386
CC := $(HOST)-elf-gcc

OUTPUT_DIR := ../../bin

override CFILES := $(shell find . -type f -name '*.c')

CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
					-I../../include -g -nostdlib

all:
	@$(foreach file, $(CFILES), $(CC) $(CFLAGS) -c $(file) -o ../../bin/$(basename $(notdir $(file))).o; echo "[CC] $(file)";)
