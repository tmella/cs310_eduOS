
#include "../drivers/screen.h"

void main () {
    clearScreen();
    print_string("Ole que funciona!!! \n"
                 "This also works", 0x0f);
}