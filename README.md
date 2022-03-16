
# Pedagogical Operating System for Undergraduates 

This operating system is a basic 32-bit x86 architecture operating system, which intends to serve as a resource for the accompanying labs 
with can be found at [Labs homepage](https://github.com/tmella/cs310_eduOS/wiki#welcome-to-the-educational-operating-system)

### Labs 
* [Lab 1: Multitasking and Scheduling
  ](https://github.com/tmella/cs310_eduOS/wiki/Lab-1:-Multitasking-and-Scheduling)
* [Lab 2: Memory Management](https://github.com/tmella/cs310_eduOS/wiki/Lab-2:-Memory-Management)
* [Lab 3: User programs](https://github.com/tmella/cs310_eduOS/wiki/Lab-3:-User-programs)


### Required resources
A helper script has been created ``dependency-installer.sh`` which will install all the needed resources to compile the project. 
All the executables will be added to a new directory ``build-tools/bin``, in the aim to not be intrusive on our system. _Only works on Mac or Linux based system_. 
> Requires make, a C compiler. Brew for Mac users
```
chmod +x dependency-installer.sh
./dependency-installer.sh

# Add all execs to PATH
export PATH="$PATH:$(pwd)/build-tools/bin"
```

The installed resources are: [qemu-system-i386](https://www.qemu.org/download/), [nasm](https://github.com/netwide-assembler/nasm), [GNU elf utils](https://github.com/nativeos/i386-elf-toolchain/releases)

***QEMU installation*** <br/>
Given the build time required by Qemu, it is easier to build from source. 

_Mac installation (requires Brew)_
```
brew install qemu
```

_Linux installation_
* Arch: ``pacman -S qemu``

* Debian/Ubuntu: ``apt-get install qemu``

* Fedora: ``dnf install @virtualization``

* Gentoo: ``emerge --ask app-emulation/qemu``

* RHEL/CentOS: ``yum install qemu-kvm``

* SUSE: ``zypper install qemu``

### Build instructions
Source code compilation:
```
 make 
```
Emulate OS on qemu (will also compile):
```
make run
```

