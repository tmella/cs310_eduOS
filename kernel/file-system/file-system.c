
#include "file.h"

// For now this is included manually

#include "../../user/user_headers.h"
#include "../../stdlib/string.h"
#include "../../stdlib/stdtypes.h"

static bin_node user_programs[] = {
    {"random", sizeof(random_bin), random_bin}
};

// Simply calls the function
void run() {
    typedef int func(void);
    func *f = (func *) random_bin;
    int i = f();
}

bin_node *find_file(char *name) {
    uint32_t size = sizeof(user_programs) / sizeof(bin_node);
    for(int i = 0; i < size; i++) {
        if(strcmp(name, user_programs[i].name) == 0) {
            return &user_programs[i];
        }
    }
    return null_ptr;
}
