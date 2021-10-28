//
// Created by University  on 28/10/21.
//

#include "../drivers/screen.h"
#include "low_level.h"

void setCursor(int offset) {
    offset = offset / 2;
    port_byte_out(REG_SCREEN_CTRL, VGA_OFFSET_HIGH);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, VGA_OFFSET_LOW);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset & 0xff));
}

int getCursor() {

    port_byte_out(REG_SCREEN_CTRL , 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;

    port_byte_out(REG_SCREEN_CTRL , 15);
    offset += port_byte_in(REG_SCREEN_DATA);

    return offset * 2;
}

int getOffset(int row, int col) {
    return ((row * MAX_COLS) + col) * 2;
}

// TODO simplify
int newLineOffset(int offset) {
    int row = offset/(2 * MAX_COLS);
    return getOffset(row+1, 0);
}

int print_chat_at_offset(char charac, char attribute_type, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    if(charac == '\n') {
        offset = newLineOffset(offset);
    } else {
        vidmem[offset] = charac;
        vidmem[offset+1] = attribute_type;

        offset += 2;
    }


    // Set cursor for next time
    setCursor(offset);

    return offset;
}

void print_char(char charac, int col, int row, char attribute_type) {
    if (!attribute_type)
        attribute_type = WHITE_ON_BLACK;

    int offset;

    if (col >= 0 && row >= 0)
        offset = ((row * MAX_COLS) + col) * 2;
    else
        offset = getCursor();

    print_chat_at_offset(charac, attribute_type, offset);
}

void clearScreen() {
    for(int row = 0; row < MAX_ROWS ; row++) {
        for(int col = 0 ; col < MAX_COLS ; col++) {
            print_char(' ', col, row, WHITE_ON_BLACK);
        }
    }
    setCursor(0);
}

void print_string(char * str, char attribute_type) {
    int offset = getCursor();
    for(int i = 0; str[i] != 0 ; i++) {
        // Returns off set in case of offset shift due to \n
        offset = print_chat_at_offset(str[i], attribute_type, offset);
    }
}





