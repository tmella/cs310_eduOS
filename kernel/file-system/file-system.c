
#include "file.h"

// For now this is included manually

#include "../../user/user_headers.h"
// Custom OS stdlib headers
#include "string.h"
#include "stdtypes.h"

static bin_node user_programs[] = {
    #include "../../user/user-files.c"
};

uint32_t file_count() {
    return sizeof(user_programs) / sizeof(bin_node);
}

bin_node *find_file(char *name) {
    uint32_t size = file_count();
    for(int i = 0; i < size; i++) {
        if(strcmp(name, user_programs[i].name) == 0) {
            return &user_programs[i];
        }
    }
    return null_ptr;
}

bin_node *get_all_executables() {
    return user_programs;
}


