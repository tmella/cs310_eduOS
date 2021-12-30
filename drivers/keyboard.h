//
// Created by University  on 1/11/21.
//

#ifndef CSWK_KEYBOARD_H
#define CSWK_KEYBOARD_H

static char letter;

void initialise_keyboard();

char blocking_wait_for_char(char ch);

#endif //CSWK_KEYBOARD_H
