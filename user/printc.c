
#include "syscall.h"

#define RED_ON_BLACK 0x01

int main(int argc, const char *argv[]) {
    print_c_syscall("I can print in color", RED_ON_BLACK);
}