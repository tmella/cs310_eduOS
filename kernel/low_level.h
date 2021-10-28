//
// Created by University  on 28/10/21.
//

#ifndef CSWK_LOW_LEVEL_H
#define CSWK_LOW_LEVEL_H

unsigned char port_byte_in(unsigned short port);

void port_byte_out(unsigned short port, unsigned char data);

unsigned short port_word_in(unsigned short port);

void port_word_out(unsigned short port, unsigned short data);

#endif //CSWK_LOW_LEVEL_H
