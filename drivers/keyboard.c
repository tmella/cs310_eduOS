

#include "../kernel/low_level.h"
#include "keyboard.h"
#include "../kernel/interrupt/idt.h"

/* Characters taken from my US Laptop keyboard layout. Should be standard */
const char ascii_map[] = {'?', '?',
                          '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '?', '?',
                          'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\\',
                          '?', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '?', '?',
                          '?', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '?'};

#define SPACE 0x39
#define BACKSPACE 0x0E
#define ENTER 0x1C

#define SC_MAX 57

static uint32_t unread;
static uint32_t next_char;
static char buffer[256];

// TODO add Capitals logic
static void keyboard_handler(i_registers_t *registers) {
    uint8_t key_code = port_byte_in(0x60);

    if (key_code > 57)
        return;

    letter = ascii_map[key_code];

    switch (key_code) {
        case SPACE:
            letter = ' ';
            break;
        case BACKSPACE: // Backspace
//            printBackspace();
            letter = '?';
            break;
        case ENTER:
            letter = '\n';
            break;
    }

    buffer[next_char++] = letter;
}

void initialise_keyboard() {
    add_handler(33, keyboard_handler);
}

char read_char() {
    // Blocking wait for there to be enough chars
    while(next_char - unread < 1);

    return buffer[unread++];
}

/* Currently, this implementation is fully blocking */
char *read_input(char *buf, int length) {
    if (length < 0)
        return 0;

    for(int i = 0; i < length; i++)
        buf[i] = read_char();

    return buf;
}

char blocking_wait_for_char(char ch) {
    while (letter != ch);
    unread++;
    return ch;
}

char get_current_letter() {
    return letter;
}
