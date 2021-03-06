
#include "shell.h"
#include "kstdlib.h"
#include "../stdlib/memory.h"
#include "../stdlib/string.h"

#include "file-system/file-system.h"

#include "../drivers/keyboard.h"
#include "../drivers/screen.h"

#include "string.h"
#include "stdtypes.h"

#include "process/process_scheduler.h"

void init_shell() {

}

void clear_shell() {
    clear_screen();
}

int parse_args(char *cmd, char **cmds) {
    int argc = 0;
    cmds[argc] = next_word(cmd);
    while(cmds[argc]) {
        cmds[++argc] = next_word(null_ptr);
    }

    return argc;
}

void execute_cmd(char *cmd) {
    char *cmds[10];

    int argc = parse_args(cmd, cmds);

    /* Empty string passed */
    if(argc == 0)
        return;


    char *fcmd = cmds[0];
    if(strcmp(fcmd, "ls") == 0) {
        bin_node *allfiles = get_all_executables();
        print_string("\n");
        for(int i = 0; i < file_count(); i++) {
            kprintf("%s    ", allfiles[i].name);
        }

    } else if(strcmp(fcmd, "clear") == 0) {
        clear_shell();
    } else {
        bin_node * exec = find_file(fcmd);
        if(exec) {
            print_new_line();
            create_user_process(fcmd, argc, cmds);
            run_process();
        } else {
            kprintf("\nUnknown command: %s", fcmd);
        }
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void run_shell() {
    kprintf_c(0x04,"\nshell> ");

    int counter = 0;
    char line_buf[128];
    while (1) {
        char value = read_char();
        if(value == '\n') {
            execute_cmd(line_buf);
            counter = 0;
            memset(line_buf, 0, 128);
            kprintf_c(0x04,"\nshell> ");
        } else if (value == '\b')  {
            print_backspace();
            line_buf[--counter] = '\0';
        }else {
            line_buf[counter++] = value;
            kprintf("%c", value);
        }
    }
}
#pragma clang diagnostic pop