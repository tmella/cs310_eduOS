#
## THIS MAKEFILE ASSUMES THAT A VERSION ABOVE 4 IS BEING USED AS IT REQUIRES WRITING TO A FILE
#
## For now this is a very basic "hardcoded" make file
## which doesnt use a crt0 file nor a standard library
#

USER_FLAGS= -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs

USER_SRC=$(filter-out crt0.c user_files.c, $(wildcard *.c))
USER_H= $(USER_SRC:.c=.bin.h)

all: user_headers.h user_files.c $(USER_H)

%.bin.h: %.bin
	xxd -i $< $@

# The address should not be changed, if necessary you will also need to change the
# process start address in its virtual memory
%.bin: crt0.o %.o
	$(LD) -m elf_i386 -O0 -o $@ -Ttext 0x500000 $^ ../stdlib/stdlib.a  --oformat binary

%.o: %.c
	$(CC) $(USER_FLAGS) -c $< -I ../stdlib -o $@

# Adds all the user files to a user_headers file
# Essentially its a hack for a fake file system
user_headers.h: $(USER_H)
	cat /dev/null > $@ # Clear the file
	for file in $^ ; do \
        echo "#include <$$(pwd)/$$file>" >> $@; \
    done

user_files.c: $(USER_SRC)
	cat /dev/null > $@ # Clear the file
	for file in $(basename $^) ; do \
        echo -n "{" >> $@; \
        echo -n "\"$$file\"," >> $@; \
        echo -n "sizeof($$file" >> $@; \
        echo -n "_bin), $$file" >> $@; \
        echo -n "_bin}," >> $@; \
    done

	truncate -s-1 $@


clean:
	$(RM) user_headers.h *.o *.bin.h