# $@ = target file
# $< = first dependency
# $^ = all dependencies

SRC = $(wildcard kernel/*.c drivers/*.c kernel/process/*.c kernel/process/tasks/*.c kernel/memory/*.c kernel/interrupt/*.c stdlib/*.c)
ASM_SRC = $(wildcard kernel/process/*.asm kernel/interrupt/*.asm)
HEADERS = $(wildcard kernel/*.h drivers/*.h kernel/process/*.h kernel/process/tasks/include/*.h kernel/memory/*.h kernel/interrupt/*.h stdlib/*.h)

OBJ = ${SRC:.c=.o}
ASM_OBJ = ${ASM_SRC:.asm=.o}

# First rule is the one executed when no parameters are fed to the Makefile
all: os-image.bin

run: os-image.bin
	qemu-system-i386 -d int -fda $<

os-image.bin: booloader_with_kernel.bin kernel.bin
	cat $^ > $@

kernel.bin:  kernel/kernel-ep.o ${OBJ} ${ASM_OBJ}
	$(LD) -m elf_i386 -o $@ -Ttext 0x10000 $^ --oformat binary

%.o: %.asm
	nasm $< -f elf -o $@

%.o: %.c
	$(CC) -m32 -ffreestanding -c $< -o $@

# Disassemble
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

booloader_with_kernel.bin: bootloader/booloader_with_kernel.asm
	nasm $< -f bin -o $@

echo: os-image.bin
	xxd $<

SRC_ASM = $(wildcard kernel/*.asm drivers/*.asm kernel/memory/*.asm kernel/interrupt/*.asm stdlib/*.asm kernel/process/*.asm)
CLEAN_ASM = ${SRC_ASM:.asm=.o}

clean:
	$(RM) *.bin *.o *.dis ${OBJ} ${CLEAN_ASM}
