#!/bin/bash

TARGET=i386
qemu-system-$TARGET -cdrom myos.iso -m 256 -no-shutdown -no-reboot -serial stdio