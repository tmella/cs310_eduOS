
# For now this is a very basic "hardcoded" make file
# which doesnt use a crt0 file nor a standard library

USER_FLAGS= -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs

all: random.bin.h

%.bin: crt0.o %.o
	$(LD) -m elf_i386 -O0 -o $@ -Ttext 0x0 crt0.o random.o --oformat binary

%.bin.h: %.bin
	xxd -i $< $@

%.o: %.c
	$(CC) $(USER_FLAGS) -c $< -o $@