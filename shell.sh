mkdir -p bin/

nasm -felf32 src/boot/boot.s -o bin/boot.o
i386-elf-gcc -c src/kernel/kernel.c -o bin/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i386-elf-gcc -T src/linker.ld -o bin/myos.bin -ffreestanding -O2 -nostdlib bin/boot.o bin/kernel.o -lgcc

mkdir -p isodir/boot/grub
cp bin/myos.bin isodir/boot/myos.bin
cp src/boot/grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o myos.iso isodir