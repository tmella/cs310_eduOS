#!/bin/sh

INSTALL_DIR=$(pwd)/"build-tools"
TOOLS_BIN=$INSTALL_DIR/bin

read -p "Are you sure you want to install all necessary dependencies?[Yy]: " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
  mkdir -p $INSTALL_DIR
  mkdir -p $INSTALL_DIR/bin

  PATH=$PATH:$TOOLS_BIN

  cd $INSTALL_DIR

  if ! command -v nasm &>/dev/null; then
    echo "Nasm not found will install to $TOOLS_BIN. Installing ..."

    if [ ! -d "nasm-2.15.05" ]; then

      if [[ $OSTYPE == 'darwin'* ]]; then
        curl -OL --silent https://www.nasm.us/pub/nasm/releasebuilds/2.15.05/macosx/nasm-2.15.05-macosx.zip
        unzip -qq nasm-2.15.05-macosx.zip
      else
        # Linux users will have to build from source
        curl -O --silent https://www.nasm.us/pub/nasm/releasebuilds/2.15.05/nasm-2.15.05.tar.gz
        tar xfz nasm-2.15.05.tar.gz
      fi
    fi

    cd nasm-2.15.05
    rm -f $TOOLS_BIN/nasm
    mv nasm ../bin
    cd ..
    rm nasm-2.15.05-macosx.zip
    rm -rf nasm-2.15.05
  fi

  # Defaulting install versions to Mac
  BINUTILS_V=
  GCC_V=

  # TODO: should probably add a check for all tools
  if ! command -v i386-elf-gcc &>/dev/null; then

    echo "Compiler and tools not found, will install at $TOOLS_BIN. Installing ..."

    if [[ $OSTYPE == 'darwin'* ]]; then
      BINUTILS_V=i386-elf-binutils-apple-darwin-x86_64.tar.bz2
      GCC_V=i386-elf-gcc-apple-darwin-x86_64.tar.bz2
    else
      BINUTILS_V=i386-elf-binutils-apple-darwin-x86_64.tar.bz2
      GCC_V=i386-elf-gcc-apple-darwin-x86_64.tar.bz2
    fi

    if [ ! -d "i386-elf-binutils" ]; then
      curl -OL --silent https://github.com/nativeos/i386-elf-toolchain/releases/download/preview/$BINUTILS_V
      tar -xf $BINUTILS_V
    fi
    cd i386-elf-binutils
    mv bin/* $TOOLS_BIN/
    cd ..
    rm -rf i386-elf-binutils
    rm $BINUTILS_V

    if [ ! -d "i386-elf-gcc" ]; then
      curl -OL --silent https://github.com/nativeos/i386-elf-toolchain/releases/download/preview/$GCC_V
      tar -xf $GCC_V
    fi
    cd i386-elf-gcc
    mv bin/* $TOOLS_BIN/
    cd ..
    rm -rf i386-elf-gcc
    rm $GCC_V

  fi

fi