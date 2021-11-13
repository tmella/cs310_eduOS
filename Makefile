# $@ = target file
# $< = first dependency
# $^ = all dependencies

SRC = $(wildcard kernel/*.c drivers/*.c utils/*.c stdlib/*.c kernel/memory/*.c kernel/interrupts/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h utils/*.h stdlib/*.h kernel/memory/*.h kernel/interrupts/*.h)

OBJ = ${SRC:.c=.o}

# First rule is the one executed when no parameters are fed to the Makefile
all: run

run: os-image.bin
	qemu-system-i386 -fda $<

os-image.bin: booloader_with_kernel.bin kernel.bin
	cat $^ > $@

kernel.bin: kernel/kernel-ep.o ${OBJ} kernel/idt_asm.o kernel/irq_asm.o
	x86_64-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.asm
	nasm $< -f elf -o $@

%.o: %.c
	x86_64-elf-gcc -m32 -ffreestanding -c $< -o $@

# Disassemble
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

booloader_with_kernel.bin: bootloader/booloader_with_kernel.asm
	nasm $< -f bin -o $@

echo: os-image.bin
	xxd $<

clean:
	$(RM) *.bin *.o *.dis ${OBJ} kernel/idt_asm.o kernel/irq_asm.o kernel/kernel-ep.o
