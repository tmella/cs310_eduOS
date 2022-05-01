
#include "screen.h"
#include "../kernel/low_level.h"

void setCursor(int offset) {
    offset = offset / 2;
    port_byte_out(REG_SCREEN_CTRL, VGA_OFFSET_HIGH);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, VGA_OFFSET_LOW);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset & 0xff));
}

int getCursor() {
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;

    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);

    return offset * 2;
}

int getOffset(int row, int col) {
    return ((row * MAX_COLS) + col) * 2;
}

int newLineOffset(int offset) {
    int row = offset / (2 * MAX_COLS);
    return getOffset(row + 1, side_margins);
}

int get_next_offset(int currentOffset) {
    // Checks if the offset at a final column
    if(((currentOffset/2)-((MAX_COLS-side_margins-1))) % MAX_COLS) {
        return currentOffset + 2;
    }
    return newLineOffset(currentOffset);
}

int print_char_at_offset_free(char ch, char attribute_type, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    if (ch == '\n') {
        offset = newLineOffset(offset);
    } else {
        vidmem[offset] = ch;
        vidmem[offset + 1] = attribute_type;

        offset = get_next_offset(offset);
    }

    return offset;
}

int print_chat_at_offset(char charac, char attribute_type, int offset) {
    int cursor_offset = print_char_at_offset_free(charac, attribute_type, offset);
    setCursor(cursor_offset);

    return cursor_offset;
}

void print_char_at(char charac, int col, int row, char attribute_type) {
    if (!attribute_type)
        attribute_type = WHITE_ON_BLACK;

    int offset;

    if (col >= 0 && row >= 0)
        offset = ((row * MAX_COLS) + col) * 2;
    else
        offset = getCursor();

    print_chat_at_offset(charac, attribute_type, offset);
}

void print_free_char(char charac, int col, int row, char attribute_type) {
    if (!attribute_type)
        attribute_type = WHITE_ON_BLACK;

    int offset;

    if (col >= 0 && row >= 0)
        offset = ((row * MAX_COLS) + col) * 2;
    else
        offset = getCursor();

    print_char_at_offset_free(charac, attribute_type, offset);
}

/* Blanks out the section indicated */
void clear_at(int col, int row) {
    print_free_char(' ', col, row, WHITE_ON_BLACK);
}

void clear_screen() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            print_char_at(' ', col, row, WHITE_ON_BLACK);
        }
    }
    setCursor(0);
}

void print_string(char *str) {
    print_string_colour(str, WHITE_ON_BLACK);
}

void print_char_colour(char chr, char colour) {
    print_chat_at_offset(chr, colour, getCursor());
}

void print_char(char chr) {
    print_char_colour(chr, WHITE_ON_BLACK);
}

void print_string_colour(char *str, char attribute_type) {
    int offset = getCursor();
    for (int i = 0; str[i] != 0; i++) {
        // Returns off set in case of offset shift due to \n
        offset = print_chat_at_offset(str[i], attribute_type, offset);
    }
}

void print_backspace() {
    int backOffset = getCursor() - 2;
    print_chat_at_offset(' ', WHITE_ON_BLACK, backOffset);
    setCursor(backOffset);
}

void print_new_line() {
    print_string("\n");
}





