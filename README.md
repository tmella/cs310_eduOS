
### Pedagogical Operating System for Undergraduates 

This operating system is a basic 32-bit x86 architecture operating system, which intends to serve as a resource for the accompanying labs 
with can be found at [Labs homepage](https://github.com/tmella/cs310_eduOS/wiki#welcome-to-the-educational-operating-system) 

### Required resources
* [qemu-system-i36](https://www.qemu.org/download/)
* [nasm](https://github.com/netwide-assembler/nasm): Assembler 
* [GNU elf utils](https://github.com/nativeos/i386-elf-toolchain/releases): this includes the compiler, linker

A helper script has been created ``dependency-installer.sh`` which will install all the needed resources to compile the project. 
All the executables will be added to a new directory ``build-tools/bin``, in the aim to not be intrusive on our system. _Only works on Mac or Linux based system_

```
chmod +x dependency-installer.sh
./dependency-installer.sh

# Add all execs to PATH
export PATH="$PATH:$(pwd)/build-tools/bin"
```

***QEMU installation*** Sadly there is a bug/incompatibility with Qemu and Darwin's SDK causes the build to fail, therefore we cannot create 
the executable from source. Therefore it will have to be installed with a package manager 

Mac installation (requires Brew)
```
brew install qemu
```

Linux installation
* Arch: ``pacman -S qemu``

* Debian/Ubuntu: ``apt-get install qemu``

* Fedora: ``dnf install @virtualization``

* Gentoo: ``emerge --ask app-emulation/qemu``

* RHEL/CentOS: ``yum install qemu-kvm``

* SUSE: ``zypper install qemu``

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