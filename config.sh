#!/bin/bash

# THIS FILE WILL STORE ALL THE NEEDED CONFIGS AND ENV VARIABLES

ORIGINAL_DIR=$(pwd)

EXECUTABLES=$(pwd)/bin/
TEMP_BUILD=$(pwd)/temp-build/

WORK_DIR=$(pwd)

# Create dir for scripts and add to PATH
mkdir -p "bin"
export PATH="$PATH:$EXECUTABLES"

\cp oshelper.sh $EXECUTABLES/oshelper
chmod u+x $EXECUTABLES/oshelper

if ! command -v hub &>/dev/null; then
  echo "Downloading hub (Github helper)"
  mkdir -p $TEMP_BUILD

  cd $TEMP_BUILD
  COMPRESSED_HUB=hub-darwin-amd64-2.14.2.tgz
  HUB_V=
  if [[ $OSTYPE == 'darwin'* ]]; then
    COMPRESSED_HUB=hub-darwin-amd64-2.14.2.tgz
    HUB_V=hub-darwin-amd64-2.14.2
    curl -LO --silent https://github.com/github/hub/releases/download/v2.14.2/$COMPRESSED_HUB
  else
    COMPRESSED_HUB=hub-linux-amd64-2.14.2.tgz
    HUB_V=hub-linux-amd64-2.14.2
    wget -cq https://github.com/github/hub/releases/download/v2.14.2/$COMPRESSED_HUB
  fi

  tar -zxf $COMPRESSED_HUB
  cp $HUB_V/bin/hub $EXECUTABLES
fi

rm -rf $TEMP_BUILD
cd $ORIGINAL_DIR

# TODO: here we should also check for required dependencies
