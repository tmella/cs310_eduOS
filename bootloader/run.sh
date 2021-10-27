#!/bin/bash


nasm booloader_with_kernel.asm -f bin -o booloader_with_kernel.bin

echo Succesfully build BIN

echo Boot sector file...
qemu-system-x86_64 booloader_with_kernel.bin