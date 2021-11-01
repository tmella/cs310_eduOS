
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "xinter.h"

void main () {
    clearScreen();
    print_string("Ole que funciona!!! \n"
                 "This also works\n", 0x0f);

    install_interrupt_service_routine();

    asm volatile("sti");

    print_string("Initialising keyboard ... \n", WHITE_ON_BLACK);
    initialise_keyboard();

}