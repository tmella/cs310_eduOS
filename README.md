
### Pedagogical Operating System for Undergraduates 

This operating system is a basic 32-bit x86 architecture operating system, which intends to serve as a resource for the accompanying labs 
with can be found at [Labs homepage](https://github.com/tmella/cs310_eduOS/wiki#welcome-to-the-educational-operating-system) 

### Required resources
* [qemu-system-i36](https://www.qemu.org/download/)
* [nasm](https://github.com/netwide-assembler/nasm): Assembler 
* [GNU elf utils](https://github.com/nativeos/i386-elf-toolchain/releases): this includes the compiler, linker

A helper script to install all needed dependencies is included in the project(TODO add):

### Build instructions
Compilation all the source code:
```
 make 
```
Emulate OS on qemu (will also compile):
```
make run
```


##Design decisions