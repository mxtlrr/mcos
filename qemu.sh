#!/bin/bash

TARGET=i386
qemu-system-$TARGET -cdrom myos.iso -no-shutdown -no-reboot -serial stdio