#!/bin/bash

OS_PROJECT=https://github.com/tmella/cs310_eduOS.git
LAB_1_BRANCH=creating-helper-script
LAB_2_BRANCH=creating-helper-script
LAB_3_BRANCH=creating-helper-script

CURRENT_LAB=""
# For now we will assume that we are on DCS systems

# Sanity check
if ! command -v git &>/dev/null; then
  echo "You must have git for this to work!!"
  exit
fi

# This is for the end when we save
#if [[ ! $(git config user.name) ]]; then
#
#  echo "Not logged in to github"
#
#  read -p "You are not logged into Github. You will not be able to save your progress. Do you still want to continue [Yy]: " -n 1 -r
#  echo    # (optional) move to a new line
#  if [[ $REPLY =~ ^[Yy]$ ]]
#  then
#      git clone $OS_PROJECT
#      git checkout -t remotes/origin/$LAB1
#  fi
#
#else
#  echo "Forking OS project"
#fi

load_lab() {
  echo "Well the first is $2"
  case $2 in
  "lab1")
    CURRENT_LAB=$LAB_1_BRANCH
    ;;
  "lab2")
    CURRENT_LAB=$LAB_2_BRANCH
    ;;
  "lab3")
    CURRENT_LAB=$LAB_3_BRANCH
    ;;

  *)
    echo "Unknown lab $2"
    exit
    ;;
  esac

  if [[ ! -z "$(git status --porcelain)" ]]; then
    echo "You have unsaved changes in your working directory"
  fi

  # If branch exists locally, else checkout remote
  if git rev-parse --verify $CURRENT_LAB &>/dev/null; then
    git checkout $CURRENT_LAB
  else
    git checkout -t remotes/origin/$CURRENT_LAB
  fi

  git fetch && git pull
}

compile_lab() {
  cd $WORK_DIR
  if [ -z "$CURRENT_LAB" ]; then
    echo "Warning: lab hasn't been loaded. Try \n oshelper load <lab_name>"
  fi
  cd $WORK_DIR
  echo "This is the dir im in $WORK_DIR"
  make -B
}

run_os() {
  compile_lab
  make run
}

save_progress() {
  # TODO check if current is empty
  # check the name of the current branch as back up

  # THEN use GITHUB hub helper to fork repo so student can push to their own repo
  echo "YET TODO"
}

print_error_msg() {
  echo "Unknown command $1 \n\n"

  echo "The following commands are available:\n\t -load \n\t -compile \n\t -run \n\t -save "

}

case $1 in
"load")
  load_lab $@
  ;;
"compile")
  compile_lab $@
  ;;
"run")
  run_os $@
  ;;
"save")
  save_progress $@
  ;;
"atom")
  atom $WORK_DIR
  ;;
*)
  print_error_msg
  ;;
esac
