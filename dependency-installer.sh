#!/bin/bash

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
    rm -f $TOOLS_BIN/nasm

    if [ ! -d "nasm-2.15.05" ]; then

      NASM_ZIP=
      if [[ $OSTYPE == 'darwin'* ]]; then
        NASM_ZIP=nasm-2.15.05-macosx.zip
        wget -cq https://www.nasm.us/pub/nasm/releasebuilds/2.15.05/macosx/nasm-2.15.05-macosx.zip
        unzip -qq nasm-2.15.05-macosx.zip
      else
        NASM_ZIP=nasm-2.15.05.tar.gz
        # Linux users will have to build from source
        wget -cq https://www.nasm.us/pub/nasm/releasebuilds/2.15.05/nasm-2.15.05.tar.gz
        tar xfz $NASM_ZIP
      fi
    fi

    cd nasm-2.15.05

    # Build from source if Linux (their package manager is "fiddly")
    if [[ $OSTYPE != 'darwin'* ]]; then
      ./configure
      make
    fi

    mv nasm $TOOLS_BIN
    mv ndisasm $TOOLS_BIN
    cd ..
    rm $NASM_ZIP
    rm -rf nasm-2.15.05
  fi

  if ! command -v x86_64-elf-gcc &>/dev/null; then
    echo "Compiler and tools not found, will install at $TOOLS_BIN. Installing ..."

    if [[ $OSTYPE == 'darwin'* ]]; then
      brew install x86_64-elf-gcc
    else
      if [ ! -d "fake" ]; then
        wget -cq https://github.com/lordmilko/i686-elf-tools/releases/download/7.1.0/x86_64-elf-tools-linux.zip
        unzip x86_64-elf-tools-linux.zip
      fi
      cd x86_64-elf
      mv bin/* $TOOLS_BIN/
      cd ..
      rm -rf x86_64-elf-tools-linux
      rm x86_64-elf-tools-linux.zip
    fi

  fi

fi
