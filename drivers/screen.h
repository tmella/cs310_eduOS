
#ifndef CSWK_SCREEN_H
#define CSWK_SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// Attribute byte for our default colour scheme.
#define WHITE_ON_BLACK 0x0f
// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

// Para que hace falta
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e

void clearScreen();

void print_new_line();

void printBackspace();

void print_char(char chr);
void print_string(char * str);
void print_string_colour(char * str, char attribute_type);

void print_char_at(char charac, int col, int row, char attribute_type);

#endif //CSWK_SCREEN_H
