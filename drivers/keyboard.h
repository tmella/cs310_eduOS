//
// Created by University  on 1/11/21.
//

#ifndef CSWK_KEYBOARD_H
#define CSWK_KEYBOARD_H

static char letter;

void initialise_keyboard();

char blocking_wait_for_char(char ch);

char read_char();
char *read_input(char *buf, int length);

#endif //CSWK_KEYBOARD_H
