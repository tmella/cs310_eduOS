
#include "file.h"

// For now this is included manually
#include "../../user/random.bin.h"

static bin_node user_programs[] = {
    {"random", sizeof(random_bin), random_bin}
};


// Simply calls the function
void run() {
    typedef int func(void);
    func* f = (func*)random_bin;
    int i = f();
}


