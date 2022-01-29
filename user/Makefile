#
## THIS MAKEFILE ASSUMES THAT A VERSION ABOVE 4 IS BEING USED AS IT REQUIRES WRITING TO A FILE
#
## For now this is a very basic "hardcoded" make file
## which doesnt use a crt0 file nor a standard library
#

USER_FLAGS= -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs

USER_SRC=$(filter-out crt0.c, $(wildcard *.c))
USER_H= $(USER_SRC:.c=.bin.h)

all: user_headers.h $(USER_H) random.bin random.o

%.bin.h: %.bin
	xxd -i $< $@

%.bin: %.o
	$(LD) -m elf_i386 -O0 -o $@ -Ttext 0x1000000 $^ --oformat binary

%.o: %.c
	$(CC) $(USER_FLAGS) -c $< -o $@

# Adds all the user files to a user_headers file
# Essentially its a hack for a fake file system
user_headers.h: $(USER_H)
	cat /dev/null > $@ # Clear the file
	for number in $^ ; do \
        echo "#include <$$(pwd)/$$number>" > $@; \
    done

clean:
	$(RM) user_headers.h *.o *.bin.h