#!/bin/bash

OS_PROJECT=https://github.com/tmella/cs310_eduOS.git
LAB_1_BRANCH=lab1
LAB_2_BRANCH=lab2
LAB_3_BRANCH=lab3

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
#  printf '\e[31m%s\e[0m' "You are not logged into Git. You will not be able to save your progress."
#
#  read -p " Do you still want to continue [Yy]: " -n 1 -r
#  echo    # (optional) move to a new line
#  if [[ $REPLY =~ ^[Yy]$ ]]
#  then
#      git clone $OS_PROJECT
#      git checkout -t remotes/origin/"$LAB1"
#  fi
#
#else
#  echo "Forking OS project"
#fi

BRCH_SUF=_work

load_lab() {
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
    printf '\e[31m%s\e[0m' "\nYou have unsaved changes in your working directory"

    read -p "The changes will be stashed. Are you sure you want to continue?[Yy]: " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit
    fi
    git stash
    printf "\n Your changes have been stashed!! \n"
  fi

  git pull --tags -f

  # If branch exists locally, else checkout remote
  if git rev-parse --verify "$CURRENT_LAB$BRCH_SUF" &>/dev/null; then
    printf "\nYou already have a local version. Will switch to that branch"
    git checkout "$CURRENT_LAB$BRCH_SUF"

    git fetch && git pull
  else
    git checkout -b "$CURRENT_LAB$BRCH_SUF" $CURRENT_LAB
  fi

}

compile_lab() {
  cd "$WORK_DIR"
  if [ -z "$CURRENT_LAB" ]; then
    printf "Warning: lab hasn't been loaded. Try \n oshelper load <lab_name>"
  fi
  cd "$WORK_DIR"
  echo "This is the dir im in $WORK_DIR"
  make -B
}

run_os() {
  compile_lab
  make run
}

save_progress() {

  if [ -z "$2" ]
    then
      echo "Missing commit message! Aborting"
      exit
  fi

  msg="${*:2}"

  git add .
  git commit -m "$msg"
}

print_error_msg() {
  printf "Unknown command $1 \n\n"

  printf "The following commands are available:\n\t -load \n\t -compile \n\t -run \n\t -save "

}

case $1 in
"load")
  load_lab "$@"
  ;;
"compile")
  compile_lab "$@"
  ;;
"run")
  run_os "$@"
  ;;
"save")
  save_progress "$@"
  ;;
"atom")
  atom "$WORK_DIR"
  ;;
*)
  print_error_msg
  ;;
esac
