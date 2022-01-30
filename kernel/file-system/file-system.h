
#ifndef CSWK_KERNEL_FILE_SYSTEM_FILE_SYSTEM_H
#define CSWK_KERNEL_FILE_SYSTEM_FILE_SYSTEM_H

#include "file.h"

uint32_t file_count();

bin_node *find_file(char *name);
bin_node *get_all_executables(void);

#endif //CSWK_KERNEL_FILE_SYSTEM_FILE_SYSTEM_H
