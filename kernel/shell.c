
#include "shell.h"
#include "../stdlib/stdlib.h"
#include "../stdlib/memory.h"

#include "../drivers/keyboard.h"
#include "../drivers/screen.h"

void init_shell() {

}

void clear_shell() {
    clearScreen();
}

void execute_cmd(char *cmd) {

    if(strcmp(cmd, "ls") == 0) {

    } else if(strcmp(cmd, "clear") == 0) {
        clear_shell();
    } else {
        printf("\nUnknown command: %s", cmd);
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void run_shell() {
    printf_c(0x04,"\nshell> ");

    int counter = 0;
    char line_buf[128];
    while (1) {

        char value = read_char();
        if(value == '\n') {
            execute_cmd(line_buf);
            counter = 0;
            memset(line_buf, 0, 128);
            printf_c(0x04,"\nshell> ");
        } else {
            line_buf[counter++] = value;
            printf("%c", value);
        }
    }
}
#pragma clang diagnostic pop