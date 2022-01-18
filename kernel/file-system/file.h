
#ifndef CSWK_KERNEL_FILE_SYSTEM_FILE_H
#define CSWK_KERNEL_FILE_SYSTEM_FILE_H

/* The implementation for this file system "hack/workaround to loading from disk" has
 * been inspired by the following OS project: https://github.com/povilasb/simple-os/blob/master/kernel/src/fileSystem.cc
 *
 * Its not a real file system as the files are not loaded from disk as an ELF (or any other executable type),
 * if not they are loaded directly into RAM on startup.
 *
 * */

#include <stdint.h>

typedef struct {
  char name[32];
  uint32_t size;
  uint8_t *data;
} bin_node;

#endif //CSWK_KERNEL_FILE_SYSTEM_FILE_H
