
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
### Set up
Start by cloning the OS repository: 
```
git clone https://github.com/tmella/cs310_eduOS.git
cd cs310_eduOS
```

#### Running on DCS
DCS systems will already have all the necessary dependencies to run the project. To set up all the required ENV variables, and helper tools (``oshelper``), go ahead and run the following:
```bash
chmod +x config.sh  && source ./config.sh 
```


#### Running locally _( Linux and OSX only )_
If you are running locally its likely you won't have the required dependencies (unless you are into OS development). The script ``dependency-installer.sh`` will take care of downloading, and building the required software, which will be added to ``build-tools/bin``. (This allows for a non-intrusive installation, just delete the directory and consider it gone). Run as follows:
```bash
chmod +x dependency-installer.sh && ./dependency-installer.sh
```
This will install the required compiler, assembler, and GNU tools required. 

***The emulator however cannot be built from source*** (unless you have specific a linux system, 35min and patience), therefore it will have to be installed traditionally with a package manager. The guide for which can be found at the [OS README](https://github.com/tmella/cs310_eduOS/blob/main/README.md)

One completed the above. You can set up your environment to run the OS with:
```bash
chmod +x config.sh # Make executable
source ./config.sh 
```

***

Finally, you can load lab 1 with the ``oshelper`` CLI:
```bash
oshelper load lab1
```
> The script, in this case, just checkouts the branch for this lab and insures that you have no unsaved 
> changes 

