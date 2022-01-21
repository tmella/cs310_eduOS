
# THIS MAKEFILE ASSUMES THAT A VERSION ABOVE 4 IS BEING USED AS IT REQUIRES WRITING TO A FILE

# For now this is a very basic "hardcoded" make file
# which doesnt use a crt0 file nor a standard library

USER_FLAGS= -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs

all: user_headers.h

all_headers= $(wildcard *.c)
user_programs = $(filter-out src/crt0.c, $(all_headers))

%.bin: crt0.o %.o
	$(LD) -m elf_i386 -O0 -o $@ -Ttext 0x0 crt0.o random.o --oformat binary

%.bin.h: %.bin
	xxd -i $< $@

%.o: %.c
	$(CC) $(USER_FLAGS) -c $< -o $@

user_headers.h: $(user_programs)
	cat /dev/null > $@ # Clear the file
	for number in $(user_programs:.c=.bin.h) ; do \
        echo "#include <$$(pwd)/$$number>" > $@; \
    done
