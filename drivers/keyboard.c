

#include "../kernel/low_level.h"
#include "keyboard.h"
#include "../kernel/inter.h"

/* Characters taken from my US Laptop keyboard layout. Should be standard */
const char ascii_map[] = {'?', '?',
                          '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '?', '?',
                          'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\\',
                          '?', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '?',
                          '?', 'z', 'x', 'c', 'v', 'b', 'n', 'b', 'n', 'm', ',', '.', '/', '?'};

#define SPACE 0x39
#define BACKSPACE 0x0E
#define ENTER 0x1C

#define SC_MAX 57

// TODO add Capitals logic
static void keyboard_handler(i_registers_t *registers) {
    uint8_t key_code = port_byte_in(0x60);

    if (key_code > 57) return;
    switch (key_code) {
        case SPACE:
            print_string(" ");
            break;
        case BACKSPACE: // Backspace
            printBackspace();
            break;
        case ENTER:
            print_new_line();
            break;
        default:
            char letter = ascii_map[key_code];
            char str[2] = {letter, '\0'};
            print_string(str);
    }
}

void initialise_keyboard() {
    add_handler(33, keyboard_handler);
}
