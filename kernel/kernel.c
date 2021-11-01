
#include "../drivers/screen.h"
#include "xinter.h"

void main () {
    clearScreen();
    print_string("Ole que funciona!!! \n"
                 "This also works", 0x0f);

    install_interrupt_service_routine();

    asm volatile ("int $0x3");
    asm volatile ("int $0x4");
}