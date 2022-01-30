

# This make file is created to build the static library

all: stdlib.a

stdlib.a: string.o syscall.o stdlib.o
	$(AR) rv $@ $^

%.o: %.c
	$(CC) -m32 -ffreestanding -c $< -o $@

clean:
	$(RM) *.o *.a